#include "stdafx.h"
#include "IGameObjectManager.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Saru.h"
#include "GameCamera.h"
#include "Title.h"

Game::Game()
{
	m_soundEnigne.Init();
	m_gameBGM.Init(L"Assets/Sound/GameBgm.wav");
	m_gameBGM.Play(true);

	m_pl = g_goMgr.NewGO<Player>();
	m_stage = g_goMgr.NewGO<Stage>();
	m_ene = g_goMgr.NewGO<Enemy>();
	m_gCamera = g_goMgr.NewGO<GameCamera>();

	m_saru[0] = g_goMgr.NewGO<Saru>();
	m_saru[1] = g_goMgr.NewGO<Saru>();

	m_saru[0]->SetPos({ 0.0f, 0.0f, 500.0f });
	m_saru[1]->SetPos({-100.0f, 0.0f, 500.0f});

	m_gCamera->SetPlayer(m_pl);
	m_ene->SetPlayer(m_pl);

	m_saru[0]->SetPlayer(m_pl);
	m_pl->SetSaru(m_saru[0]);
	m_saru[1]->SetPlayer(m_pl);
	m_pl->SetSaru(m_saru[1]);

}


Game::~Game()
{
	g_goMgr.DeleteGO(m_pl);
	g_goMgr.DeleteGO(m_stage);
	g_goMgr.DeleteGO(m_ene);
	g_goMgr.DeleteGO(m_gCamera);
	g_goMgr.DeleteGO(m_saru[0]);
	g_goMgr.DeleteGO(m_saru[1]);

	g_goMgr.NewGO<Title>();
}

void Game::Update()
{
	if (g_pad[0].IsTrigger(enButtonSelect)) {
		g_goMgr.DeleteGO(this);
	}
	if (m_pl->GetSaruCount() == 2)
	{
		g_goMgr.DeleteGO(this);
	}

	//サウンドエンジンを更新
	m_soundEnigne.Update();
}

void Game::Draw()
{
}