#include "stdafx.h"
#include "PlayerStateAttacked.h"
#include "Player.h"

const float PLAYER_FUTTOBI_DECAY = 0.9998f;		//吹っ飛び速度を減衰。
const float PLAYER_FUTTOBI_STRIDE = 0.3f;		//踏ん張り力。
const float PLAYER_FUTTOBI_TIME = 0.3f;			//吹っ飛び時間。

void PlayerStateAttacked::OnEnter()
{
	m_timer = 0.0f;
}

void PlayerStateAttacked::Update()
{
	m_timer += GameTime().GetFrameDeltaTime();
	if (m_timer < PLAYER_FUTTOBI_TIME) {
		//吹っ飛び速度を減衰させる。
		m_player->m_attackedPower *= PLAYER_FUTTOBI_DECAY;
	}
	else {
		//踏ん張る。
		m_player->m_attackedPower *= PLAYER_FUTTOBI_STRIDE;
	}
	m_player->GetMoveSpd() = m_player->m_attackedPower;
	m_player->ChangeStateWaitAnim();
}

void PlayerStateAttacked::OnLeave()
{
	
}
