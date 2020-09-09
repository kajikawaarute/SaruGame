#include "stdafx.h"
#include "Fade.h"
#include "IGameObjectManager.h"

Fade::Fade()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_device = g_graphicsEngine->GetDevice();

	//画像の読み込み。
	DirectX::CreateDDSTextureFromFile(
		m_device,							//デバイス
		L"Assets/sprite/Fade.dds",		//読み込む画像ファイル
		nullptr,
		&m_shaderResourceView				//読み込んだファイルの情報を格納
	);
}


Fade::~Fade()
{
}

void Fade::Update()
{
	switch (m_state) {
	case enState_FadeIn:	//フェードイン
		m_alpha -= m_alphaIncAmount;
		if (m_alpha <= 0.0f)
		{
			m_alpha = 0.0f;
		}
		break;
	case enState_FadeOut:	//フェードアウト
		m_alpha += m_alphaIncAmount;
		if (m_alpha >= 1.0f)
		{
			m_alpha = 1.0f;
		}
		break;
	case enState_Idle:

		break;
	}
}

void Fade::Draw()
{
	SpriteBatctDraw();
}

void Fade::SpriteBatctDraw()
{

	DirectX::FXMVECTOR m_alphaColor = { 0.0f, 0.0f, 0.0f, m_alpha };		//カラー。

	m_spriteBatch->Begin();
	m_spriteBatch->Draw(
		m_shaderResourceView,							//読み込んだ画像ファイル
		DirectX::XMFLOAT2(m_positionX, m_positionY),	//画像の座標
		nullptr,										//スプライトを任意の領域に表示
		m_alphaColor,									//カラー
		m_rotation,										//回転角度
		DirectX::XMFLOAT2(0.0f, 0.0f),					//回転軸の位置
		m_scale,										//拡大率
		DirectX::SpriteEffects::SpriteEffects_None,		//スプライトの表示反転
		m_depth											//スプライトの深度を指定
	);
	m_spriteBatch->End();
}
