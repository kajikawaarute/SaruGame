#include "stdafx.h"
#include "Enemy.h"
#include "EnemyStateWait.h"
#include "Player.h"

const float ENEMY_MOVE_CHANGE_DISTANCE = 400.0f;	//移動状態に切り替わる距離。
const float ENEMY_ANGLE = 160;						//エネミーの視野

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
	if (fabsf(angle) < CMath::DegToRad(ENEMY_ANGLE) && toEnemyLen < ENEMY_MOVE_CHANGE_DISTANCE) {
		m_enemy->ChangeStateMove();
	}
}

void EnemyStateWait::OnLeave()
{
}
