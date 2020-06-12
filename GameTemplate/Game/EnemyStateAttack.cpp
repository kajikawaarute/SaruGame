#include "stdafx.h"
#include "Enemy.h"
#include "EnemyStateAttack.h"

void EnemyStateAttack::OnEnter()
{
	m_enemy->Attack();
}

void EnemyStateAttack::Update()
{
	m_enemy->AddWaitTimer();
	if (m_enemy->GetWaitTimer() > 60) {
		m_enemy->ChangeStateWait();
		m_enemy->ReSetWaitTimer();
	}
}

void EnemyStateAttack::OnLeave()
{
}
