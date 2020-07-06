#include "stdafx.h"
#include "ButtonUI.h"
#include "IGameObjectManager.h"

ButtonUI::ButtonUI()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();

	m_device = g_graphicsEngine->GetDevice();

	DirectX::CreateDDSTextureFromFile(
		m_device,							//デバイス
		L"Resource/sprite/Button_UI.dds",		//読み込む画像ファイル
		nullptr,
		&m_shaderResourceView				//読み込んだファイルの情報を格納
	);
}

ButtonUI::~ButtonUI()
{
}

void ButtonUI::Update()
{
}

void ButtonUI::Draw()
{
	SpriteBatch();
}

void ButtonUI::SpriteBatch()
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(
		m_shaderResourceView,							//読み込んだ画像ファイル
		DirectX::XMFLOAT2(m_positionX, m_positionY),	//画像の座標
		nullptr,											//スプライトを任意の領域に表示
		color,												//カラー
		m_rotation,										//回転角度
		DirectX::XMFLOAT2(0.0f, 0.0f),						//回転軸の位置
		m_scale,											//拡大率
		DirectX::SpriteEffects::SpriteEffects_None,			//スプライトの表示反転
		m_depth											//スプライトの深度を指定
	);
	m_spriteBatch->End();
}
