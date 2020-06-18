#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "IGameObjectManager.h"

const float ENEMY_MOVE_SPPED = 5.0f;		//�G�l�~�[�̈ړ����x�B
const float ENEMY_FUTTOBI_POWER = 1000.0f;	//�v���C���[�𐁂���΂��́B

Enemy::Enemy()
{
	m_model.Init(L"Assets/modelData/Enemy.cmo");

	//�A�j���[�V�����̃��[�h
	m_animationClip[enAnim_walk].Load(L"Assets/animData/Enemy-walk.tka");
	m_animationClip[enAnim_wait].Load(L"Assets/animData/Enemy-taiki.tka");

	m_enemyDeathEffekt = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/EnemyDeath.efk");

	//�A�j���[�V�����̃��[�v��ݒ�
	m_animationClip[enAnim_walk].SetLoopFlag(true);
	m_animationClip[enAnim_wait].SetLoopFlag(true);

	//�A�j���[�V������������
	m_animation.Init(m_model, m_animationClip, enAnim_num);

	//��Ԃ�����������B
	m_enemyStateAttack.Init(this);
	m_enemyStateWait.Init(this);
	m_enemyStateMove.Init(this);

	//�G�l�~�[�̏������
	m_currentState = &m_enemyStateWait;

	//�G�l�~�[�̏����A�j���[�V����
	m_enAnimClip = enAnim_wait;
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//�G�l�~�[�̏��
	m_currentState->Update();
	ChangeState(m_enEnemyState);

	//�G�l�~�[�̃A�j���[�V����
	switch (m_enAnimClip)
	{
	case enAnim_wait:
		m_animation.Play(enAnim_wait, m_animTime);
		break;
	case enAnim_walk:
		m_animation.Play(enAnim_walk, m_animTime);
		break;
	}

	m_animation.Update(1.0f / 30.0f);

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Enemy::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Enemy::Move()
{
	m_moveSpeed.Normalize();
	m_moveSpeed.x *= ENEMY_MOVE_SPPED;
	m_moveSpeed.z *= ENEMY_MOVE_SPPED;
	m_moveSpeed.y = 0.0f;
	m_position += m_moveSpeed;

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

void Enemy::Attack()
{
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toEnemyDir = m_pl->GetPos() - m_position;

	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toEnemyDir.x, toEnemyDir.z));
	toEnemyDir.Normalize();

	m_pl->SetAttackedPower( toEnemyDir * ENEMY_FUTTOBI_POWER );
	m_pl->Attacked();
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

	if (toEnemyLen < 90.0f) {
		m_enEnemyState = enState_attack;
	}
}

void Enemy::Delete()
{
	m_playEffectHandle = g_effekseerManager->Play(m_enemyDeathEffekt, m_position.x, m_position.y, m_position.z);

	g_goMgr.DeleteGO(this);
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
