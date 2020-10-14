#include "stdafx.h"
#include "SaruCounter.h"

SaruCounter::SaruCounter()
{
}


SaruCounter::~SaruCounter()
{
	DeleteGO(m_fontRender);
}

bool SaruCounter::Start()
{
	m_fontRender = NewGO<FontRender>();
	m_fontRender->SetPosition(m_fontPosition);
	m_fontRender->SetScale(m_fontScale);

	return true;
}

void SaruCounter::Update()
{
	swprintf(m_text, L"Mission:ƒTƒ‹‚ð•ß‚Ü‚¦‚æ‚¤(%d/%d)", m_saruCounter, m_saruCount);
}

void SaruCounter::Draw()
{
	m_fontRender->SetText(m_text);
}
