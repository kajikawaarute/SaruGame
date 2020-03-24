#include "stdafx.h"
#include "Title.h"
#include "IGameObjectManager.h"
#include "Game.h"

Title::Title()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_device = g_graphicsEngine->GetDevice();
	//�摜�̓ǂݍ���
	DirectX::CreateDDSTextureFromFile(
		m_device,							//�f�o�C�X
		L"Assets/sprite/title-kari.dds",
		nullptr,
		&m_shaderResourceView				//�ǂݍ��񂾃t�@�C���̏����i�[
	);
}


Title::~Title()
{
}

void Title::Update()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{
		m_game = g_goMgr.NewGO<Game>();
		g_goMgr.DeleteGO(this);
	}
}

void Title::Draw()
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(
		m_shaderResourceView,			//�ǂݍ��񂾉摜�t�@�C��
		DirectX::XMFLOAT2(300.0f, 100.0f)	//�摜�̍��W
	);
	m_spriteBatch->End();
}
