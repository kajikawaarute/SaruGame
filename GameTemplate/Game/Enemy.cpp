#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

const float ENEMY_GRAVITY = 5000.0f;					//�G�l�~�[�ɂ�����d��(�P��cm/�b)�B
const float ENEMY_MOVE_SPPED = 400.0f;					//�G�l�~�[�̈ړ����x�B
const float ENEMY_FOUND_PLAYER_DISTANCE = 90.0f;		//�G�l�~�[���v���C���[�������鋗���B
const float ENEMY_DEATH_SE_VOLUME = 1.5f;				//�G�l�~�|���|���ꂽ����SE�̃{�����[��

Enemy::Enemy()
{
	//���f���̏������B
	m_skinModel = NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/Enemy.cmo");

	//�A�j���[�V�����̃��[�h�B
	m_animationClip[enAnim_walk].Load(L"Assets/animData/Enemy-walk.tka");
	m_animationClip[enAnim_wait].Load(L"Assets/animData/Enemy-taiki.tka");

	//�A�j���[�V�����̃��[�v��ݒ�B
	m_animationClip[enAnim_walk].SetLoopFlag(true);
	m_animationClip[enAnim_wait].SetLoopFlag(true);

	//�A�j���[�V�������������B
	m_animation.Init(m_skinModel->GetSkinModel(), m_animationClip, enAnim_num);

	//�G�l�~�[�̏����A�j���[�V�����B
	m_enAnimClip = enAnim_wait;

	//�V���h�E���V�[�o�[��ݒ�B
	m_skinModel->SetShadowReciever();

	//�G�t�F�N�g�̐����B
	m_enemyDeathEffekt = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/EnemyDeath.efk");

	//��Ԃ�����������B
	m_enemyStateAttack.Init(this);
	m_enemyStateWait.Init(this);
	m_enemyStateMove.Init(this);

	//�G�l�~�[�̏�����ԁB
	m_currentState = &m_enemyStateWait;
}


Enemy::~Enemy()
{
	//�X�L�����f�����폜�B
	DeleteGO(m_skinModel);
}

bool Enemy::Start()
{
	//�L�����N�^�[�R���g���[���[�̏������B
	m_charaCon.Init(30.0f, 30.0f, m_position);

	return true;
}

void Enemy::Update()
{
	m_moveSpeed.y -= ENEMY_GRAVITY * GameTime().GetFrameDeltaTime();

	//�G�l�~�[�̏��
	m_currentState->Update();
	ChangeState(m_enEnemyState);

	//�G�l�~�[�̃A�j���[�V����
	switch (m_enAnimClip)
	{
	case enAnim_wait:	//�ҋ@�A�j���[�V�����B
		m_animation.Play(enAnim_wait, m_animTime);
		break;
	case enAnim_walk:	//�����A�j���[�V����
		m_animation.Play(enAnim_walk, m_animTime);
		break;
	}

	//�A�j���[�V�����̍X�V�B
	m_animation.Update(GameTime().GetFrameDeltaTime());

	//�V���h�E�L���X�^�[��ݒ�B
	m_skinModel->SetShadowCaster();

	//�g�D�[�������_��ݒ�B
	m_skinModel->SetToonRender();

	//�L�����N�^�[�R���g���[���[�̍X�V�B
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);

	//�X�L�����f���̍��W��ݒ�B
	m_skinModel->SetPosition(m_position);

	//�X�L�����f���̉�]��ݒ�B
	m_skinModel->SetRotation(m_rotation);
}

void Enemy::Move()
{
	m_moveSpeed.Normalize();
	m_moveSpeed.x *= ENEMY_MOVE_SPPED;
	m_moveSpeed.z *= ENEMY_MOVE_SPPED;

	Turn();
}


void Enemy::Turn()
{
	CVector3 toEnemyDir = m_pl->GetPos() - m_position;
	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toEnemyDir.x, toEnemyDir.z));

}

void Enemy::AttackDistance()
{
	CVector3 enemyFoward = CVector3::AxisZ();
	m_rotation.Multiply(enemyFoward);
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toEnemyDir = m_pl->GetPos() - m_position;
	float toEnemyLen = toEnemyDir.Length();
	toEnemyDir.Normalize();

	float d = enemyFoward.Dot(toEnemyDir);
	float angle = acos(d);

	//�v���C���[��������B
	if (toEnemyLen < ENEMY_FOUND_PLAYER_DISTANCE) {
		m_enEnemyState = enState_attack;
	}
}

void Enemy::Delete()
{
	//�G�t�F�N�g��\���B
	m_playEffectHandle = g_effekseerManager->Play(m_enemyDeathEffekt, m_position.x, m_position.y, m_position.z);

	//�T�E���h�̍Đ��B
	prefab::CSoundSource* enemySE_Death = NewGO<prefab::CSoundSource>();
	enemySE_Death->Init(L"Assets/Sound/EnemySE_Death.wav");
	enemySE_Death->Play(false);
	enemySE_Death->SetVolume(ENEMY_DEATH_SE_VOLUME);

	DeleteGO(this);
	m_pl->DeleteEnemy(this);
}

void Enemy::ChangeState(EnEnemyState nextState)
{
	IEnenyState* pNextState = nullptr;
	EnAnimationClip nextAnimClip = enAnim_wait;
	switch (nextState)
	{
	case enState_wait:
		//���݂̏�Ԃ�ҋ@��Ԃɂ���B
		pNextState = &m_enemyStateWait;
		nextAnimClip = enAnim_wait;
		break;
	case enState_move:
		//���݂̏�Ԃ��ړ���Ԃɂ���B
		pNextState = &m_enemyStateMove;
		nextAnimClip = enAnim_walk;
		break;
	case enState_attack:
		//���݂̏�Ԃ��U����Ԃɂ���B
		pNextState = &m_enemyStateAttack;
		break;
	}
	if (pNextState != nullptr && pNextState != m_currentState) {
		//���݂̏�ԂƈႤ�B
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
