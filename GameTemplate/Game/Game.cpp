#include "stdafx.h"
#include "IGameObjectManager.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Saru.h"
#include "GameCamera.h"
#include "BananaPeel.h"

Game::Game()
{
	m_soundEnigne.Init();
	m_gameBGM.Init(L"Assets/Sound/GameBgm.wav");
	m_gameBGM.Play(true);

	//Effekseer���������B
	InitEffekseer();
	//�G�t�F�N�g�����[�h
	m_effekt = Effekseer::Effect::Create(m_effekseerManager, (const EFK_CHAR*)L"Assets/effect/test.efk");
	//�G�t�F�N�g���Đ�
	m_playEffectHandle = m_effekseerManager->Play(m_effekt, 0.0f, 0.0f, 0.0f);

	m_pl = g_goMgr.NewGO<Player>();
	m_stage = g_goMgr.NewGO<Stage>();
	m_ene = g_goMgr.NewGO<Enemy>();
	m_gCamera = g_goMgr.NewGO<GameCamera>();
	m_banana = g_goMgr.NewGO<BananaPeel>();

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

	//Effekseer���X�V
	m_effekseerManager->Update();

	if (g_pad[0].IsTrigger(enButtonA)) {
		//�Đ����̃G�t�F�N�g���~�߂�B
		m_effekseerManager->StopEffect(m_playEffectHandle);
		//�Đ��B
		m_playEffectHandle = m_effekseerManager->Play(m_effekt, 0.0f, 0.0f, 0.0f);
	}
}

void Game::Draw()
{
	m_effekseerRenderer->BeginRendering();
	m_effekseerManager->Draw();
	m_effekseerRenderer->EndRendering();
}

void Game::InitEffekseer()
{
	//�����_���[���������B
	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3D�f�o�C�X�B
		g_graphicsEngine->GetD3DDeviceContext(),	//D3D�f�o�C�X�R���e�L�X�g�B
		20000										//�|���̍ő吔�B
	);
	//�G�t�F�N�g�}�l�[�W�����������B
	m_effekseerManager = Effekseer::Manager::Create(10000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());
}
