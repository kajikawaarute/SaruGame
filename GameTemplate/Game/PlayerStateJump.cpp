#include "stdafx.h"
#include "PlayerStateJump.h"
#include "Player.h"

void PlayerStateJump::OnEnter()
{
}

void PlayerStateJump::Update()
{
	m_player->Move();
	m_player->SaruGet();
	m_player->AttackTry();
	m_player->ChangeStateWaitIsOnGound();
}

void PlayerStateJump::OnLeave()
{
}
