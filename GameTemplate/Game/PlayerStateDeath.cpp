#include "stdafx.h"
#include "PlayerStateDeath.h"
#include "Player.h"

void PlayerStateDeath::OnEnter()
{
}

void PlayerStateDeath::Update()
{
	m_player->m_moveSpeed.x = 0.0f;
	m_player->m_moveSpeed.z = 0.0f;
}

void PlayerStateDeath::OnLeave()
{
}
