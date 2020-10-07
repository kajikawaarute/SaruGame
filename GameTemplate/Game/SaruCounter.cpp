#include "stdafx.h"
#include "SaruCounter.h"
#include "IGameObjectManager.h"

SaruCounter::SaruCounter()
{
}


SaruCounter::~SaruCounter()
{
}

bool SaruCounter::Start()
{
	m_fontRender = g_goMgr.NewGO<FontRender>();
	m_fontRender->SetPosition(m_fontPosition);

	return true;
}

void SaruCounter::Update()
{
	swprintf(m_text, L"ƒTƒ‹ %d/%d", m_saruCounter, m_saruCount);
}

void SaruCounter::Draw()
{
	m_fontRender->SetText(m_text);
}
