#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "EnemyStateAttack.h"

const int ENEMY_WAIT_TIME = 60;				//エネミーが待機状態になるタイム。
const float ENEMY_FUTTOBI_POWER = 2000.0f;	//プレイヤーを吹っ飛ばす力。

void EnemyStateAttack::OnEnter()
{
	m_enemy->m_moveSpeed.x = 0.0f;
	m_enemy->m_moveSpeed.z = 0.0f;

	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toEnemyDir = m_enemy->m_pl->GetPos() - m_enemy->m_position;

	m_enemy->m_rotation.SetRotation(CVector3::AxisY(), atan2f(toEnemyDir.x, toEnemyDir.z));
	toEnemyDir.Normalize();

	m_enemy->m_pl->SetAttackedPower(toEnemyDir * ENEMY_FUTTOBI_POWER);
	m_enemy->m_pl->Attacked();
}

void EnemyStateAttack::Update()
{
	m_enemy->AddWaitTimer();
	if (m_enemy->GetWaitTimer() > ENEMY_WAIT_TIME) {
		m_enemy->ChangeStateWait();
		m_enemy->ReSetWaitTimer();
	}
}

void EnemyStateAttack::OnLeave()
{
}
