#include "stdafx.h"
#include "Enemy.h"
#include "EnemyStateWait.h"

void EnemyStateWait::OnEnter()
{
}

void EnemyStateWait::Update()
{
	m_enemy->SetChangeStateWait();
}

void EnemyStateWait::OnLeave()
{
}
