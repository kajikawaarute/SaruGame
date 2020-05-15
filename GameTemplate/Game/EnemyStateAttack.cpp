#include "stdafx.h"
#include "Enemy.h"
#include "EnemyStateAttack.h"

void EnemyStateAttack::OnEnter()
{
}

void EnemyStateAttack::Update()
{
	m_enemy->Attack();
	m_enemy->AddWaitTimer();
	if (m_enemy->GetWaitTimer() > 60) {
		m_enemy->ChangeStateWait();
		m_enemy->ReSetWaitTimer();
	}
}

void EnemyStateAttack::OnLeave()
{
}
