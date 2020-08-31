#include "stdafx.h"
#include "GunEnemyStateAttack.h"
#include "GunEnemy.h"
#include "Player.h"

void GunEnemyStateAttack::OnEnter()
{
	
}

void GunEnemyStateAttack::Update()
{
	m_gunEnemy->Attack();
	CVector3 toGunEnemyDir = m_gunEnemy->m_position - m_gunEnemy->m_player->GetPos();
	float toGunEnemyLen = toGunEnemyDir.Length();
	toGunEnemyDir.Normalize();

	if (toGunEnemyLen > 800.0f) {
		m_gunEnemy->m_enGunEnemyState = m_gunEnemy->enState_wait;
	}
}

void GunEnemyStateAttack::OnLeave()
{
}
