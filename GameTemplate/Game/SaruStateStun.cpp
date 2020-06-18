#include "stdafx.h"
#include "SaruStateStun.h"
#include "Saru.h"

void SaruStateStun::OnEnter()
{
	m_saru->m_playEffectHandle = g_effekseerManager->Play(m_saru->m_saruDamegeEffect, 
		m_saru->m_position.x, m_saru->m_position.y, m_saru->m_position.z);
}

void SaruStateStun::Update()
{
	m_saru->m_moveSpeed.x = 0.0f;
	m_saru->m_moveSpeed.z = 0.0f;

	m_saru->m_enSaruState = m_saru->enState_stun;
	m_saru->ChangeStateWaitAnim();
}

void SaruStateStun::OnLeave()
{
}
