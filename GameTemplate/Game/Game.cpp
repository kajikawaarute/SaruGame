#include "stdafx.h"
#include "IGameObjectManager.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Saru.h"
#include "GameCamera.h"
#include "BananaPeel.h"
#include "DirectXTK/Inc/SpriteBatch.h"

Game::Game()
{
	m_soundEnigne.Init();
	m_gameBGM.Init(L"Assets/Sound/GameBgm.wav");
	m_gameBGM.Play(true);

	//spriteBatchの初期化
	//m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_deviceContext);

	//画像の読み込み
	//DirectX::CreateDDSTextureFromFile(
	//	m_device,							//デバイス
	//	L"Resource/sprite/title-kari.dds",
	//	nullptr,
	//	&m_shaderResourceView				//読み込んだファイルの情報を格納
	//);

	m_pl = g_goMgr.NewGO<Player>();
	m_stage = g_goMgr.NewGO<Stage>();
	m_ene = g_goMgr.NewGO<Enemy>();
	m_gCamera = g_goMgr.NewGO<GameCamera>();

	m_saru[0] = g_goMgr.NewGO<Saru>();
	m_saru[1] = g_goMgr.NewGO<Saru>();

	m_banaPeel = g_goMgr.NewGO<BananaPeel>();
	m_banaPeel->SetPlayer(m_pl);

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
}

void Game::Update()
{
	//サウンドエンジンを更新
	m_soundEnigne.Update();
}

void Game::Draw()
{
	/*m_effekseerRenderer->BeginRendering();
	m_effekseerManager->Draw();
	m_effekseerRenderer->EndRendering();*/

	//m_spriteBatch.get()->Begin();
	//m_spriteBatch.get()->Draw(
	//	m_shaderResourceView,			//読み込んだ画像ファイル
	//	DirectX::XMFLOAT2(0.0f, 0.0f)	//画像の座標
	//);
	//m_spriteBatch.get()->End();
}