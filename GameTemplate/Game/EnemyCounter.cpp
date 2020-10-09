#include "stdafx.h"
#include "EnemyCounter.h"
#include "EnemyCounter.h"


EnemyCounter::EnemyCounter()
{
}


EnemyCounter::~EnemyCounter()
{
	g_goMgr.DeleteGO(m_fontRender);
}

bool EnemyCounter::Start()
{
	m_fontRender = g_goMgr.NewGO<FontRender>();
	m_fontRender->SetPosition(m_fontPosition);
	m_fontRender->SetScale(m_fontScale);

	return true;
}

void EnemyCounter::Update()
{
	swprintf(m_text, L"Mission:エネミーを倒そう(%d/%d)", m_enemyCounter, m_enemyCount);
}

void EnemyCounter::Draw()
{
	m_fontRender->SetText(m_text);
}
