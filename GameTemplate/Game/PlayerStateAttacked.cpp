#include "stdafx.h"
#include "PlayerStateAttacked.h"
#include "Player.h"

void PlayerStateAttacked::OnEnter()
{
	m_timer = 0.0f;
}

void PlayerStateAttacked::Update()
{
	m_timer += GameTime().GetFrameDeltaTime();
	if (m_timer < 0.3f) {
		//������ё��x������������B
		m_player->m_attackedPower *= 0.9998f;
	}
	else {
		//���񒣂�B
		m_player->m_attackedPower *= 0.3f;
	}
	m_player->GetMoveSpd() = m_player->m_attackedPower;
	m_player->ChangeStateWaitAnim();
}

void PlayerStateAttacked::OnLeave()
{
	
}
