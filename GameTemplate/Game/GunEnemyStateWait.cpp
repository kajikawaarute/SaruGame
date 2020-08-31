#include "stdafx.h"
#include "GunEnemyStateWait.h"
#include "GunEnemy.h"

void GunEnemyStateWait::OnEnter()
{
}

void GunEnemyStateWait::Update()
{
	m_gunEnemy->AttackDistance();
}

void GunEnemyStateWait::OnLeave()
{
}
