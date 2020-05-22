#include "stdafx.h"
#include "Enemy.h"
#include "EnemyStateWait.h"
#include "Player.h"

void EnemyStateWait::OnEnter()
{
}

void EnemyStateWait::Update()
{
	CVector3 enemyFoward = CVector3::AxisZ();
	m_enemy->m_rotation.Multiply(enemyFoward);
	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toEnemyDir = m_enemy->m_pl->GetPos() - m_enemy->m_position;
	float toEnemyLen = toEnemyDir.Length();
	toEnemyDir.Normalize();
	float d = enemyFoward.Dot(toEnemyDir);
	float angle = acos(d);

	m_enemy->AttackDistance();
	m_enemy->m_moveSpeed = CVector3::Zero();
	if (fabsf(angle) < CMath::DegToRad(90.0f) && toEnemyLen < 700.0f) {
		m_enemy->ChangeStateMove();
	}
}

void EnemyStateWait::OnLeave()
{
}
