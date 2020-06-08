#include "stdafx.h"
#include "IGameObjectManager.h"
#include "Game.h"
#include "Stage.h"
#include "GameCamera.h"
#include "Title.h"
#include "PlayerHP.h"
#include "GameClear.h"
#include "GameOver.h"

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
	g_goMgr.DeleteGO(m_gameClear);
	g_goMgr.DeleteGO(m_gameOver);

	g_goMgr.NewGO<Title>();
}

void Game::Update()
{
	if (g_pad[0].IsTrigger(enButtonSelect)) {
		g_goMgr.DeleteGO(this);
	}
	if (m_pl->GetSaruCount() == 3)
	{
		m_gameClearTimer++;
		if (m_gameClearTimer == 30) {
			m_gameClear = g_goMgr.NewGO<GameClear>();
		}
		if (m_gameClearTimer == 120) {
			g_goMgr.DeleteGO(this);
		}
	}
	if (m_playerHP->GetGameOver() == true) {
		m_gameClearTimer++;
		if (m_gameClearTimer == 30) {
			m_gameOver = g_goMgr.NewGO<GameOver>();
		}
		if (m_gameClearTimer == 120) {
			g_goMgr.DeleteGO(this);
		}
	}
}

void Game::Draw()
{
}