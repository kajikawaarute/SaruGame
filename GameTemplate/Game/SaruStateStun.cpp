#include "stdafx.h"
#include "SaruStateStun.h"
#include "Saru.h"

void SaruStateStun::OnEnter()
{
}

void SaruStateStun::Update()
{
	m_saru->Stun();
}

void SaruStateStun::OnLeave()
{
}
