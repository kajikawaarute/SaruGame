#include "stdafx.h"
#include "IGameObjectManager.h"
#include "Game.h"
#include "Stage.h"
#include "GameCamera.h"
#include "Title.h"
#include "PlayerHP.h"
#include "GameClear.h"

Game::Game()
{
	m_gameBGM.Init(L"Assets/Sound/GameBgm.wav");
	m_gameBGM.Play(true);

	m_stage = g_goMgr.NewGO<Stage>();
	m_pl = m_stage->GetPlayer();

	m_gCamera = g_goMgr.NewGO<GameCamera>();
	m_gCamera->SetPlayer(m_stage->GetPlayer());

	m_playerHP = g_goMgr.NewGO<PlayerHP>();
	m_pl->SetPlayerHP(m_playerHP);
}


Game::~Game()
{
	g_goMgr.DeleteGO(m_playerHP);
	g_goMgr.DeleteGO(m_gCamera);
	g_goMgr.DeleteGO(m_stage);

	g_goMgr.NewGO<Title>();
}

void Game::Update()
{
	if (g_pad[0].IsTrigger(enButtonSelect)) {
		g_goMgr.DeleteGO(this);
	}
	if (m_pl->GetSaruCount() == 3)
	{
		g_goMgr.DeleteGO(this);
	}
	if (m_playerHP->GetGameOver() == true) {
		g_goMgr.DeleteGO(this);
	}
}

void Game::Draw()
{
}