#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "IGameObjectManager.h"

Enemy::Enemy()
{
	m_model.Init(L"Assets/modelData/Enemy.cmo");

	//�A�j���[�V�����̃��[�h
	m_animationClip[enAnim_walk].Load(L"Assets/animData/Enemy-walk.tka");
	m_animationClip[enAnim_wait].Load(L"Assets/animData/Enemy-taiki.tka");

	//�A�j���[�V�����̃��[�v��ݒ�
	m_animationClip[enAnim_walk].SetLoopFlag(true);
	m_animationClip[enAnim_wait].SetLoopFlag(true);

	//�A�j���[�V������������
	m_animation.Init(m_model, m_animationClip, enAnim_num);

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
	m_currentState->Init(this);
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
	m_moveSpeed.x *= 5.0f;
	m_moveSpeed.z *= 5.0f;
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
	m_pl->GetMoveSpd() = toEnemyDir * 2.0f;
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
	g_goMgr.DeleteGO(this);
	m_pl->DeleteEnemy(this);
}

void Enemy::SetChangeStateWait()
{
	CVector3 enemyFoward = CVector3::AxisZ();
	m_rotation.Multiply(enemyFoward);
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toEnemyDir = m_pl->GetPos() - m_position;
	float toEnemyLen = toEnemyDir.Length();
	toEnemyDir.Normalize();
	float d = enemyFoward.Dot(toEnemyDir);
	float angle = acos(d);

	m_enAnimClip = enAnim_wait;
	AttackDistance();
	m_moveSpeed = CVector3::Zero();
	if (fabsf(angle) < CMath::DegToRad(90.0f) && toEnemyLen < 700.0f) {
		m_enEnemyState = enState_move;
	}
}

void Enemy::SetChangeStateMove()
{
	CVector3 enemyFoward = CVector3::AxisZ();
	m_rotation.Multiply(enemyFoward);
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toEnemyDir = m_pl->GetPos() - m_position;
	float toEnemyLen = toEnemyDir.Length();
	toEnemyDir.Normalize();

	m_enAnimClip = enAnim_walk;
	Move();
	AttackDistance();
	m_moveSpeed = toEnemyDir;
	if (toEnemyLen > 700.0f) {
		m_enEnemyState = enState_wait;
	}
}

void Enemy::ChangeState(EnEnemyState nextState)
{
	if (m_currentState != nullptr) {
		//�I������
		m_currentState->OnLeave();
	}
	switch (nextState)
	{
	case enState_wait:
		//���݂̏�Ԃ�ҋ@��Ԃɂ���B
		m_currentState = &m_enemyStateWait;
		break;
	case enState_move:
		//���݂̏�Ԃ��ړ���Ԃɂ���B
		m_currentState = &m_enemyStateMove;
		break;
	case enState_attack:
		//���݂̏�Ԃ��U����Ԃɂ���B
		m_currentState = &m_enemyStateAttack;
		break;
	}
	//�J�n����
	m_currentState->OnEnter();
}
