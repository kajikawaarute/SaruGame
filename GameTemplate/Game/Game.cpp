#include "stdafx.h"
#include "IGameObjectManager.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Saru.h"
#include "GameCamera.h"

Game::Game()
{
	m_soundEnigne.Init();
	m_gameBGM.Init(L"Assets/Sound/GameBgm.wav");
	m_gameBGM.Play(true);


	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_device = g_graphicsEngine->GetDevice();
	//�摜�̓ǂݍ���
	DirectX::CreateDDSTextureFromFile(
		m_device,							//�f�o�C�X
		L"Assets/sprite/title-kari.dds",
		nullptr,
		&m_shaderResourceView				//�ǂݍ��񂾃t�@�C���̏����i�[
	);

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
}

void Game::Update()
{
	//�T�E���h�G���W�����X�V
	m_soundEnigne.Update();
}

void Game::Draw()
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(
		m_shaderResourceView,			//�ǂݍ��񂾉摜�t�@�C��
		DirectX::XMFLOAT2(10.0f, 10.0f)	//�摜�̍��W
	);
	m_spriteBatch->End();
}