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


	//Effekseerを初期化。
	InitEffekseer();
	//エフェクトをロード
	m_effekt = Effekseer::Effect::Create(m_effekseerManager, (const EFK_CHAR*)L"Assets/effect/test.efk");
	//エフェクトを再生
	//m_playEffectHandle = m_effekseerManager->Play(m_effekt, 0.0f, 0.0f, 0.0f);

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

	//Effekseerを更新
	m_effekseerManager->Update();

	//if (g_pad[0].IsTrigger(enButtonA)) {
	//	//再生中のエフェクトを止める。
	//	m_effekseerManager->StopEffect(m_playEffectHandle);
	//	//再生。
	//	m_playEffectHandle = m_effekseerManager->Play(m_effekt, 0.0f, 0.0f, 0.0f);
	//}
	
}

void Game::Draw()
{
	m_effekseerRenderer->BeginRendering();
	m_effekseerManager->Draw();
	m_effekseerRenderer->EndRendering();

	//m_spriteBatch.get()->Begin();
	//m_spriteBatch.get()->Draw(
	//	m_shaderResourceView,			//読み込んだ画像ファイル
	//	DirectX::XMFLOAT2(0.0f, 0.0f)	//画像の座標
	//);
	//m_spriteBatch.get()->End();
}

void Game::InitEffekseer()
{
	//レンダラーを初期化。
	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3Dデバイス。
		g_graphicsEngine->GetD3DDeviceContext(),	//D3Dデバイスコンテキスト。
		20000										//板ポリの最大数。
	);
	//エフェクトマネージャを初期化。
	m_effekseerManager = Effekseer::Manager::Create(10000);

	// 描画用インスタンスから描画機能を設定
	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());
}
