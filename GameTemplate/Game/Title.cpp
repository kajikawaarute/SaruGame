#include "stdafx.h"
#include "Title.h"
#include "IGameObjectManager.h"
#include "Game.h"

Title::Title()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_device = g_graphicsEngine->GetDevice();
	//画像の読み込み
	DirectX::CreateDDSTextureFromFile(
		m_device,							//デバイス
		L"Assets/sprite/title-kari.dds",
		nullptr,
		&m_shaderResourceView				//読み込んだファイルの情報を格納
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
		m_shaderResourceView,			//読み込んだ画像ファイル
		DirectX::XMFLOAT2(300.0f, 100.0f)	//画像の座標
	);
	m_spriteBatch->End();
}
