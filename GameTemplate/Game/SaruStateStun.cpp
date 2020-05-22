#include "stdafx.h"
#include "SaruStateStun.h"
#include "Saru.h"

void SaruStateStun::OnEnter()
{
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
