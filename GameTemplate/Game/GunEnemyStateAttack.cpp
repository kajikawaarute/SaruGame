#include "stdafx.h"
#include "GunEnemyStateAttack.h"
#include "GunEnemy.h"
#include "Player.h"

const float GUNENEMY_WAIT_DISTANCE = 700.0f;	//待機状態になる距離。

void GunEnemyStateAttack::OnEnter()
{
	
}

void GunEnemyStateAttack::Update()
{
	m_gunEnemy->Attack();
	CVector3 toGunEnemyDir = m_gunEnemy->m_position - m_gunEnemy->m_player->GetPos();
	float toGunEnemyLen = toGunEnemyDir.Length();
	toGunEnemyDir.Normalize();

	//待機状態になる範囲。
	if (toGunEnemyLen > GUNENEMY_WAIT_DISTANCE) {
		m_gunEnemy->m_enGunEnemyState = m_gunEnemy->enState_wait;
	}
}

void GunEnemyStateAttack::OnLeave()
{
}
