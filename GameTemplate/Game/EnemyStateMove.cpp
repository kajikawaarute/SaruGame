#include "stdafx.h"
#include "Enemy.h"
#include "EnemyStateMove.h"
#include "Player.h"

const float ENEMY_WAIT_CHANGE_DISTANCE = 600.0f;	//待機状態に切り替わる距離。

void EnemyStateMove::OnEnter()
{
}

void EnemyStateMove::Update()
{
	CVector3 enemyFoward = CVector3::AxisZ();
	m_enemy->m_rotation.Multiply(enemyFoward);
	//エネミーからプレイヤーに伸びるベクトルを求める。
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
