#include "stdafx.h"
#include "PlayerStateAttack.h"
#include "Player.h"
#include "Enemy.h"
#include "GunEnemy.h"
#include "Saru.h"

void PlayerStateAttack::OnEnter()
{
}

void PlayerStateAttack::Update()
{
	m_player->Attack();

	m_player->ChangeStateWaitAnim();
}

void PlayerStateAttack::OnLeave()
{
	
}
