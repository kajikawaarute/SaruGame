#include "stdafx.h"
#include "Enemy.h"
#include "EnemyStateMove.h"
#include "Player.h"

const float ENEMY_WAIT_CHANGE_DISTANCE = 600.0f;	//�ҋ@��Ԃɐ؂�ւ�鋗���B

void EnemyStateMove::OnEnter()
{
}

void EnemyStateMove::Update()
{
	CVector3 enemyFoward = CVector3::AxisZ();
	m_enemy->m_rotation.Multiply(enemyFoward);
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toEnemyDir = m_enemy->m_pl->GetPos() - m_enemy->m_position;
	float toEnemyLen = toEnemyDir.Length();
	toEnemyDir.Normalize();

	m_enemy->Move();
	m_enemy->AttackDistance();
	m_enemy->m_moveSpeed = toEnemyDir;
	if (toEnemyLen > ENEMY_WAIT_CHANGE_DISTANCE) {
		m_enemy->ChangeStateWait();
	}
}

void EnemyStateMove::OnLeave()
{
}
