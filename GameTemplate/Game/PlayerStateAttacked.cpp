#include "stdafx.h"
#include "PlayerStateAttacked.h"
#include "Player.h"

const float PLAYER_FUTTOBI_DECAY = 0.9998f;		//������ё��x�������B
const float PLAYER_FUTTOBI_STRIDE = 0.3f;		//���񒣂�́B
const float PLAYER_FUTTOBI_TIME = 0.3f;			//������ю��ԁB

void PlayerStateAttacked::OnEnter()
{
	m_timer = 0.0f;
}

void PlayerStateAttacked::Update()
{
	m_timer += GameTime().GetFrameDeltaTime();
	if (m_timer < PLAYER_FUTTOBI_TIME) {
		//������ё��x������������B
		m_player->m_attackedPower *= PLAYER_FUTTOBI_DECAY;
	}
	else {
		//���񒣂�B
		m_player->m_attackedPower *= PLAYER_FUTTOBI_STRIDE;
	}
	m_player->GetMoveSpd() = m_player->m_attackedPower;
	m_player->ChangeStateWaitAnim();
}

void PlayerStateAttacked::OnLeave()
{
	
}
