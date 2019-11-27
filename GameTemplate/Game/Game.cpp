#include "stdafx.h"
#include "IGameObjectManager.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"

Game::Game()
{
	m_pl = g_goMgr.NewGO<Player>();
	m_stage = g_goMgr.NewGO<Stage>();
	m_ene = g_goMgr.NewGO<Enemy>();
	m_gCamera = g_goMgr.NewGO<GameCamera>();
	m_gCamera->SetPlayer(m_pl);
	m_ene->SetPlayer(m_pl);

	//メインとなるレンダリングターゲットを作成する。
	m_mainRenderTarget.Create(FRAME_BUFFER_W, FRAME_BUFFER_H, DXGI_FORMAT_R8G8B8A8_UNORM);

	//
	m_copyMainRtToFrameBufferSprite.Init(m_mainRenderTarget.GetRenderTargetSRV(), FRAME_BUFFER_W, FRAME_BUFFER_H);
}


Game::~Game()
{
}

void Game::Update()
{
	
}

void Game::Draw()
{
}
