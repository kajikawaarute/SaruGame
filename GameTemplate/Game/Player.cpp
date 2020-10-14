#include "stdafx.h"
#include "Player.h"
#include "Saru.h"
#include "Enemy.h"
#include "GunEnemy.h"
#include "PlayerHP.h"
#include "IPlayerState.h"

const float PLAYER_GRAVITY = 5000.0f;		//�v���C���[�ɂ�����d��(�P��cm/�b)�B
const float PLAYER_JUMP_POWER = 2000.0f;	//�v���C���[���W�����v�����Ƃ��ɉ��Z����鑬�x�B
const float PLAYER_MOVE_SPEED = 850.0f;		//�v���C���[�̈ړ����x�B
const float PLAYER_SARU_DISTANCE = 300.0f;	//�v���C���[�ƃT���̋����B
const float PLAYER_SWORD_SE_VOLUME = 0.9f;	//�v���C���[���U�����Ă��鎞��SE�̃{�����[���B

Player::Player()
{
	//�L�����N�^�[�R���g���[���[�̏�����
	m_charaCon.Init(50.0f, 100.0f, m_position);

	//�v���C���[�̏������
	m_currentState = &m_playerStateWait;
}


Player::~Player()
{
	DeleteGO(m_skinModel);
}

bool Player::Start()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_skinModel = NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/Player.cmo");

	//�v���C���[�̃A�j���[�V���������[�h
	m_animationClip[enAnim_walk].Load(L"Assets/animData/Player-walk.tka");
	m_animationClip[enAnim_wait].Load(L"Assets/animData/Player-taiki.tka");
	m_animationClip[enAnim_saruGet].Load(L"Assets/animData/Player-SaruGet.tka");
	m_animationClip[enAnim_attacked].Load(L"Assets/animData/Player-attacked2.tka");
	m_animationClip[enAnim_jump].Load(L"Assets/animData/Player-jump.tka");
	m_animationClip[enAnim_sliped].Load(L"Assets/animData/Player-Slip.tka");
	m_animationClip[enAnim_attack].Load(L"Assets/animData/Player-attack.tka");
	m_animationClip[enAnim_death].Load(L"Assets/animData/Player-death.tka");

	//�A�j���[�V�����̃��[�v�ݒ�B
	m_animationClip[enAnim_walk].SetLoopFlag(true);
	m_animationClip[enAnim_wait].SetLoopFlag(true);

	//�A�j���[�V������������
	m_animation.Init(m_skinModel->GetSkinModel(), m_animationClip, enAnim_num);

	//�v���C���[�̏����A�j���[�V����
	m_enAnimClip = enAnim_wait;

	//�V���h�E���V�[�o�[��ݒ�B
	m_skinModel->SetShadowReciever();

	return true;
}

void Player::Update()
{
	//�v���C���[�̏d��
	m_moveSpeed.y -= PLAYER_GRAVITY *  GameTime().GetFrameDeltaTime();

	//�v���C���[�̏��
	m_currentState->Init(this);
	m_currentState->Update();
	ChangeState(m_enPlayerState);

	//�v���C���[�̃A�j���[�V����
	switch (m_enAnimClip)
	{
	case enAnim_wait:		//�ҋ@�A�j���[�V����
		m_animation.Play(enAnim_wait, animTime);
		break;
	case enAnim_walk:		//�����A�j���[�V����
		m_animation.Play(enAnim_walk, animTime);
		break;
	case enAnim_saruGet:	//�T���̕ߊl�A�j���[�V����
		m_animation.Play(enAnim_saruGet, animTime);
		break;
	case enAnim_attacked:	//�U�����ꂽ�Ƃ��̃A�j���[�V����
		m_animation.Play(enAnim_attacked, animTime);
		break;
	case enAnim_jump:		//�W�����v�A�j���[�V����
		m_animation.Play(enAnim_jump, animTime);
		break;
	case enAnim_sliped:		//�����Ă��鎞�̃A�j���[�V����
		m_animation.Play(enAnim_sliped, animTime);
		break;
	case enAnim_attack:		//�U���A�j���[�V����
		m_animation.Play(enAnim_attack, animTime);
		break;
	case enAnim_death:		//���S�A�j���[�V����
		m_animation.Play(enAnim_death, animTime);
		break;
	}
	//�A�j���[�V�����̍X�V�B
	m_animation.Update(GameTime().GetFrameDeltaTime());

	//�V���h�E�L���X�^�[��ݒ�B
	m_skinModel->SetShadowCaster();

	//�V���h�E�}�b�v�̍쐬
	ShadowMap::GetInstance().UpdateShadowMap(
		m_position + CVector3::One() * 4000.0f,
		m_position
	);

	//�g�D�[�������_�[��ݒ�B
	m_skinModel->SetToonRender();

	//�L�����R���̍X�V�B
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);

	//���W��ݒ�B
	m_skinModel->SetPosition(m_position);

	//��]��ݒ�B
	m_skinModel->SetRotation(m_rotation);
}

void Player::Move()
{
	float StickZ = g_pad[0].GetLStickYF() * PLAYER_MOVE_SPEED;
	float StickX = g_pad[0].GetLStickXF() * PLAYER_MOVE_SPEED;

	CVector3 cameraForward = g_camera3D.GetTarget() - g_camera3D.GetPosition();
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	m_moveSpeed.x = cameraForward.x * StickZ;
	m_moveSpeed.z = cameraForward.z * StickZ;

	CVector3 cameraRight;
	cameraRight.Cross({ 0.0f, 1.0f, 0.0f }, cameraForward);
	cameraRight.Normalize();
	m_moveSpeed += cameraRight * StickX;


	Turn();
}

void Player::GetSaru()
{
	CVector3 plFoward = CVector3::AxisZ();
	m_rotation.Multiply(plFoward);
	//�T������v���C���[�ɐL�т�x�N�g�������߂�B
	for (int i = 0; i < m_sarus.size(); i++) {
		CVector3 toPlayerDir = m_sarus[i]->GetPos() - m_position;
		float toEnemyLen = toPlayerDir.Length();
		toPlayerDir.Normalize();

		float d = plFoward.Dot(toPlayerDir);
		float angle = acos(d);

		//�T����߂܂���͈́B
		if (fabsf(angle) < CMath::DegToRad(45.0f) && toEnemyLen < PLAYER_SARU_DISTANCE)
		{
			m_sarus[i]->GetSaru();
		}
	}
}

void Player::Turn()
{
	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);

	m_rotation.SetRotation(CVector3::AxisY(), angle);
}

void Player::DeleteSaru(Saru* saru)
{
	for (auto it = m_sarus.begin(); it != m_sarus.end();) {
		if (*it == saru) {
			it = m_sarus.erase(it);
			m_saruCount++;
		}
		else {
			//���N�G�X�g���󂯂Ă��Ȃ��B
			it++;
		}
	}
}

void Player::DeleteEnemy(Enemy * enemy)
{
	for (auto it = m_enemys.begin(); it != m_enemys.end();) {
		if (*it == enemy) {
			it = m_enemys.erase(it);
			m_enemyCount++;
		}
		else {
			//���N�G�X�g���󂯂Ă��Ȃ��B
			it++;
		}
	}
}

void Player::DeleteGunEnemy(GunEnemy * gunEnemy)
{
	for (auto it = m_gunEnemys.begin(); it != m_gunEnemys.end();) {
		if (*it == gunEnemy) {
			it = m_gunEnemys.erase(it);
			m_enemyCount++;
		}
		else {
			//���N�G�X�g���󂯂Ă��Ȃ��B
			it++;
		}
	}
}

void Player::Attacked()
{
	//�U�����󂯂��t���O
	m_playerHp->SetDamageFlag(true);
	m_enPlayerState = enState_attacked;

	//�T�E���h�̍Đ��B
	prefab::CSoundSource* playerSE_damage = NewGO<prefab::CSoundSource>();
	playerSE_damage->Init(L"Assets/Sound/PlayerSE_Damage.wav");
	playerSE_damage->Play(false);
}

void Player::Sliped()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//��]����B
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), 5.0f);
	m_rotation.Multiply(addRot);
}

void Player::Jump()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{
		//�W�����v����
		m_moveSpeed.y = PLAYER_JUMP_POWER;
		m_enPlayerState = enState_Jump;

		//�T�E���h�̍Đ��B
		prefab::CSoundSource* playerSE_Jump = NewGO<prefab::CSoundSource>();
		playerSE_Jump->Init(L"Assets/Sound/PlayerSE_Jump.wav");
		playerSE_Jump->Play(false);
	}
}

void Player::SaruGet()
{
	if (g_pad[0].IsTrigger(enButtonX))
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;

		//�T�E���h�̍Đ��B
		prefab::CSoundSource* playerSE_Ami = NewGO<prefab::CSoundSource>();
		playerSE_Ami->Init(L"Assets/Sound/PlayerSE_Ami.wav");
		playerSE_Ami->Play(false);
		m_enPlayerState = enState_saruGet;
	}
	
}

void Player::AttackTry()
{
	if (g_pad[0].IsTrigger(enButtonB))
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;

		m_enPlayerState = enState_attack;

		//�T�E���h�̍Đ��B
		prefab::CSoundSource* playerSE_sword = NewGO<prefab::CSoundSource>();
		playerSE_sword->Init(L"Assets/Sound/PlayerSE_sword.wav");
		playerSE_sword->Play(false);
		playerSE_sword->SetVolume(PLAYER_SWORD_SE_VOLUME);
	}
}

void Player::StateDeath()
{
	m_enPlayerState = enState_death;
}

void Player::ChangeStateWaitAnim()
{
	if (m_animation.IsPlaying() != true) {
		m_enPlayerState = enState_wait;
	}
}

void Player::ChangeStateWaitIsOnGound()
{
	if (m_charaCon.IsOnGround()) {
		m_enPlayerState = enState_wait;
	}
}

void Player::ChangeState(EnPlayerState nextState)
{
	IPlayerState* pNextState = nullptr;
	EnAnimationClip nextAnimClip = enAnim_wait;
	switch (m_enPlayerState)
	{
	case Player::enState_wait:
		//���݂̏�Ԃ�ҋ@��Ԃɂ���B
		pNextState = &m_playerStateWait;
		nextAnimClip = enAnim_wait;
		break;
	case Player::enState_walk:
		//���݂̏�Ԃ��ړ���Ԃɂ���B
		pNextState = &m_playerStateMove;
		nextAnimClip = enAnim_walk;
		break;
	case Player::enState_saruGet:
		//���݂̏�Ԃ��T����ߊl��Ԃɂ���B
		pNextState = &m_playerStateSaruGet;
		nextAnimClip = enAnim_saruGet;
		break;
	case Player::enState_attacked:
		//���݂̏�Ԃ��U�����ꂽ��Ԃɂ���B
		pNextState = &m_playerStateAttacked;
		nextAnimClip = enAnim_attacked;
		break;
	case Player::enState_Jump:
		//���݂̏�Ԃ��W�����v��Ԃɂ���B
		pNextState = &m_playerStateJump;
		nextAnimClip = enAnim_jump;
		break;
	case Player::enState_sliped:
		//���݂̏�Ԃ������Ă����Ԃɂ���B
		pNextState = &m_playerStateSliped;
		nextAnimClip = enAnim_sliped;
		break;
	case Player::enState_attack:
		//���݂̏�Ԃ��U����Ԃɂ���B
		pNextState = &m_playerStateAttack;
		nextAnimClip = enAnim_attack;
		break;
	case Player::enAnim_death:
		//���݂̏�Ԃ����S��Ԃɂ���B
		pNextState = &m_playerStateDeath;
		nextAnimClip = enAnim_death;
		break;
	}
	if (pNextState != nullptr && pNextState != m_currentState) {
		if (m_currentState != nullptr) {
			//�I������
			m_currentState->OnLeave();
		}
		m_currentState = pNextState;
		m_enAnimClip = nextAnimClip;
		//�J�n����
		m_currentState->OnEnter();
	}
}
