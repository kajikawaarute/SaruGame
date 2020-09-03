#include "stdafx.h"
#include "SaruStateAttack.h"
#include "Saru.h"

void SaruStateAttack::OnEnter()
{
	m_saru->Attack();
}

void SaruStateAttack::Update()
{
	if (m_saru->m_animation.IsPlaying() != true) {
		m_saru->ChangeStateWait();
	}
}

void SaruStateAttack::OnLeave()
{
}
