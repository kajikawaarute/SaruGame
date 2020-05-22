#include "stdafx.h"
#include "SaruStateAttack.h"
#include "Saru.h"

void SaruStateAttack::OnEnter()
{
}

void SaruStateAttack::Update()
{
	m_saru->Attack();

	m_saru->AddWaitTimer();
	if (m_saru->GetWaitTimer() > 60) {
		m_saru->ChangeStateWait();
		m_saru->ReSetWaitTimer();
	}
}

void SaruStateAttack::OnLeave()
{
}
