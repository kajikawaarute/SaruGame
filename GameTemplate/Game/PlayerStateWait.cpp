#include "stdafx.h"
#include "PlayerStateWait.h"
#include "Player.h"

void PlayerStateWait::OnEnter()
{
}

void PlayerStateWait::Update()
{
	m_player->Move();
	CVector3 moveSpeedXZ = m_player->m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	if (moveSpeedXZ.LengthSq() >= 1.0f * 1.0f) {
		m_player->m_enPlayerState = m_player->enState_walk;
	}
	m_player->SaruGet();
	m_player->Jump();
	m_player->AttackTry();
}

void PlayerStateWait::OnLeave()
{
}
