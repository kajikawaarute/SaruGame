#include "stdafx.h"
#include "Enemy.h"
#include "EnemyStateMove.h"

void EnemyStateMove::OnEnter()
{
}

void EnemyStateMove::Update()
{
	m_enemy->SetChangeStateMove();
}

void EnemyStateMove::OnLeave()
{
}
