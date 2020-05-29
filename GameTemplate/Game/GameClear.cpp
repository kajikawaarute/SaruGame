#include "stdafx.h"
#include "GameClear.h"
#include "IGameObjectManager.h"

GameClear::GameClear()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_device = g_graphicsEngine->GetDevice();
	DirectX::CreateDDSTextureFromFile(
		m_device,
		L"Assets/sprite/PlayerHP.dds",
		nullptr,
		&m_shaderResourceView
	);
}

GameClear::~GameClear()
{
}

void GameClear::Update()
{
}

void GameClear::Draw()
{
	SpriteBatchDraw();
}

void GameClear::SpriteBatchDraw()
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(
		m_shaderResourceView,							//読み込んだ画像ファイル
		DirectX::XMFLOAT2(m_positionX, m_positionY),	//画像の座標
		nullptr,										//スプライトを任意の領域に表示
		color,											//カラー
		m_rotation,										//回転角度
		DirectX::XMFLOAT2(0.0f, 0.0f),					//回転軸の位置
		m_scale,										//拡大率
		DirectX::SpriteEffects::SpriteEffects_None,		//スプライトの表示反転
		m_depth											//スプライトの深度を指定
	);
	m_spriteBatch->End();
}
