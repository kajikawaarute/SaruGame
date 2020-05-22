#include "stdafx.h"
#include "SaruStateGet.h"
#include "Saru.h"

void SaruStateGet::OnEnter()
{
}

void SaruStateGet::Update()
{
	m_saru->m_deathTimer++;
	if (m_saru->m_deathTimer == 1) {
		//エフェクトを再生。
		m_saru->m_playEffectHandle = m_saru->m_effekseerManager->Play(m_saru->m_effekt, m_saru->m_position.x, 
			m_saru->m_position.y, m_saru->m_position.z);
	}
	if (m_saru->m_deathTimer == 40) {
		m_saru->Death();
	}
}

void SaruStateGet::OnLeave()
{
}