#include "stdafx.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "Saru.h"
#include "Enemy.h"
#include "PlayerHP.h"
#include "graphics/ShadowMap.h"

const float PLAYER_GRAVITY = 5000.0f;		//�v���C���[�ɂ�����d��(�P��cm/�b)�B
const float PLAYER_JUMP_POWER = 2000.0f;	//�v���C���[���W�����v�����Ƃ��ɉ��Z����鑬�x�B
const float PLAYER_MOVE_SPEED = 1000.0f;	//�v���C���[�̈ړ����x�B

Player::Player()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/Player.cmo");

	//�L�����N�^�[�R���g���[���[�̏�����
	m_charaCon.Init(50.0f, 100.0f, m_position);
	
	//�Ղꂢ��[�̃A�j���[�V���������[�h
	m_animationClip[enAnim_walk].Load(L"Assets/animData/Player-walk.tka");
	m_animationClip[enAnim_wait].Load(L"Assets/animData/Player-taiki.tka");
	m_animationClip[enAnim_saruGet].Load(L"Assets/animData/Player-SaruGet.tka");
	m_animationClip[enAnim_attacked].Load(L"Assets/animData/Player-attacked2.tka");
	m_animationClip[enAnim_jump].Load(L"Assets/animData/Player-jump.tka");
	m_animationClip[enAnim_sliped].Load(L"Assets/animData/Player-Slip.tka");
	m_animationClip[enAnim_attack].Load(L"Assets/animData/Player-attack.tka");
	m_animationClip[enAnim_death].Load(L"Assets/animData/Player-death.tka");

	m_animationClip[enAnim_walk].SetLoopFlag(true);
	m_animationClip[enAnim_wait].SetLoopFlag(true);

	//�A�j���[�V������������
	m_animation.Init(m_model, m_animationClip, enAnim_num);

	//�v���C���[�̏����A�j���[�V����
	m_enAnimClip = enAnim_wait;

	//�v���C���[�̏������
	//m_enPlayerState = enState_taiki;
	m_currentState = &m_playerStateWait;

	m_model.SetShadowReciever(true);
}


Player::~Player()
{
}

void Player::Update()
{
	m_moveSpeed.y -= PLAYER_GRAVITY *  GameTime().GetFrameDeltaTime();

	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);

	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

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
		//m_player_walkSE.Play(false);
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

	m_animation.Update(1.0f / 30.0f);

	ShadowMap::GetInstance().RegistShadowCaster(&m_model);

	//�V���h�E�}�b�v�̍쐬
	ShadowMap::GetInstance().UpdateShadowMap(
		m_position + CVector3::One() * 4000.0f,
		m_position
	);
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

void Player::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
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

		if (fabsf(angle) < CMath::DegToRad(45.0f) && toEnemyLen < 300.0f)
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
			//it++;
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
			//it++;
		}
		else {
			//���N�G�X�g���󂯂Ă��Ȃ��B
			it++;
		}
	}
}

void Player::Attacked()
{
	m_playerHp->SetDamageFlag(true);
	m_enPlayerState = enState_attacked;
}

void Player::Sliped()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), 5.0f);
	m_rotation.Multiply(addRot);
}

void Player::Jump()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{
		prefab::CSoundSource* player_JumpSE = g_goMgr.NewGO<prefab::CSoundSource>();
		player_JumpSE->Init(L"Assets/Sound/PlayerSE_Jump.wav");
		player_JumpSE->Play(false);

		m_moveSpeed.y = PLAYER_JUMP_POWER;
		m_enPlayerState = enState_Jump;
	}
}

void Player::SaruGet()
{
	if (g_pad[0].IsTrigger(enButtonX))
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;

		prefab::CSoundSource* player_AmiSE = g_goMgr.NewGO<prefab::CSoundSource>();
		player_AmiSE->Init(L"Assets/Sound/PlayerSE_Ami.wav");
		player_AmiSE->Play(false);
		m_enPlayerState = enState_saruGet;
	}
	
}

void Player::AttackTry()
{
	if (g_pad[0].IsTrigger(enButtonB))
	{
		m_enPlayerState = enState_attack;
	}
}

void Player::Attack()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	CVector3 plFoward = CVector3::AxisZ();
	m_rotation.Multiply(plFoward);
	//�G�l�~�[��|��
	for (int i = 0; i < m_enemys.size(); i++) {
		CVector3 toPlayer_EnemyDir = m_enemys[i]->GetPos() - m_position;
		float toEnemyLen = toPlayer_EnemyDir.Length();
		toPlayer_EnemyDir.Normalize();

		float d = plFoward.Dot(toPlayer_EnemyDir);
		float angle = acos(d);

		if (fabsf(angle) < CMath::DegToRad(45.0f) && toEnemyLen < 300.0f)
		{
			m_enemys[i]->Delete();
		}
	}

	//�T�����Ђ�܂���
	for (int i = 0; i < m_sarus.size(); i++) {
		CVector3 toPlayer_SaruDir = m_sarus[i]->GetPos() - m_position;
		float toSaruLen = toPlayer_SaruDir.Length();
		toPlayer_SaruDir.Normalize();

		float d = plFoward.Dot(toPlayer_SaruDir);
		float angle = acos(d);

		if (fabsf(angle) < CMath::DegToRad(45.0f) && toSaruLen < 300.0f)
		{
			m_sarus[i]->Stun();
		}
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
