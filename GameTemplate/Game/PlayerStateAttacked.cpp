#include "stdafx.h"
#include "PlayerStateAttacked.h"
#include "Player.h"

void PlayerStateAttacked::OnEnter()
{
}

void PlayerStateAttacked::Update()
{
}

void PlayerStateAttacked::OnLeave()
{
	m_player->ChangeStateWaitAnim();
}
