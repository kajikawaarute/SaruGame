#include "stdafx.h"
#include "Enemy.h"
#include "EnemyStateAttack.h"

const int ENEMY_WAIT_TIME = 60;		//�G�l�~�[���ҋ@��ԂɂȂ�^�C���B

void EnemyStateAttack::OnEnter()
{
	m_enemy->Attack();
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
