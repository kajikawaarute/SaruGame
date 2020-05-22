#include "stdafx.h"
#include "PlayerStateMove.h"
#include "Player.h"

void PlayerStateMove::OnEnter()
{
}

void PlayerStateMove::Update()
{
	m_player->Move();
	CVector3 moveSpeedXZ = m_player->m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	if (moveSpeedXZ.LengthSq() <= 1.0f * 1.0f) {
		m_player->m_enPlayerState = m_player->enState_wait;
	}
	m_player->SaruGet();
	m_player->Jump();
	m_player->AttackTry();
	
}

void PlayerStateMove::OnLeave()
{
}
