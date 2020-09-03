#include "stdafx.h"
#include "SaruStateGet.h"
#include "Saru.h"

void SaruStateGet::OnEnter()
{
	m_saru->SaruGetSound();
	//エフェクトを再生。
		m_saru->m_playEffectHandle = g_effekseerManager->Play(m_saru->m_saruGetEffekt, m_saru->m_position.x,
																m_saru->m_position.y, m_saru->m_position.z);
}

void SaruStateGet::Update()
{
	if (m_saru->m_animation.IsPlaying() != true) {
		m_saru->Death();
	}
}

void SaruStateGet::OnLeave()
{
}