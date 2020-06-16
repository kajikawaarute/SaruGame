#include "stdafx.h"
#include "SaruStateAttack.h"
#include "Saru.h"

void SaruStateAttack::OnEnter()
{
	m_saru->Attack();
}

void SaruStateAttack::Update()
{
	m_saru->AddWaitTimer();
	if (m_saru->GetWaitTimer() > 30) {
		m_saru->ChangeStateWait();
		m_saru->ReSetWaitTimer();
	}
}

void SaruStateAttack::OnLeave()
{
}
