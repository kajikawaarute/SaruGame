#include "stdafx.h"
#include "SaruStateAttack.h"
#include "Saru.h"

const int SARU_WAIT_TIME = 30;		//待機状態に切り替えるタイム。

void SaruStateAttack::OnEnter()
{
	m_saru->Attack();
}

void SaruStateAttack::Update()
{
	m_saru->AddWaitTimer();
	if (m_saru->GetWaitTimer() > SARU_WAIT_TIME) {
		m_saru->ChangeStateWait();
		m_saru->ReSetWaitTimer();
	}
}

void SaruStateAttack::OnLeave()
{
}
