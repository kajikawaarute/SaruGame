#include "stdafx.h"
#include "GunEnemyStateAttack.h"
#include "GunEnemy.h"
#include "Player.h"

const float GUNENEMY_WAIT_DISTANCE = 700.0f;	//�ҋ@��ԂɂȂ鋗���B

void GunEnemyStateAttack::OnEnter()
{
	
}

void GunEnemyStateAttack::Update()
{
	m_gunEnemy->Attack();
	CVector3 toGunEnemyDir = m_gunEnemy->m_position - m_gunEnemy->m_player->GetPos();
	float toGunEnemyLen = toGunEnemyDir.Length();
	toGunEnemyDir.Normalize();

	//�ҋ@��ԂɂȂ�͈́B
	if (toGunEnemyLen > GUNENEMY_WAIT_DISTANCE) {
		m_gunEnemy->m_enGunEnemyState = m_gunEnemy->enState_wait;
	}
}

void GunEnemyStateAttack::OnLeave()
{
}
