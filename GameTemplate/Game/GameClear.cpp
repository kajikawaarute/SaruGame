#include "stdafx.h"
#include "GameClear.h"
#include "IGameObjectManager.h"
#include "Fade.h"

const float GAMECLEAR_POSITION_Y = 100.0f;		//ゲームオーバーの文字が落ちる座標Y
const float GAMECLEAR_MOVE_SPEED = 10.0f;	//ゲームオーバーの文字が落ちる速度。

GameClear::GameClear()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_device = g_graphicsEngine->GetDevice();

	//画像の読み込み。
	DirectX::CreateDDSTextureFromFile(
		m_device,
		L"Assets/sprite/GAMECLEAR.dds",
		nullptr,
		&m_shaderResourceView
	);
}

GameClear::~GameClear()
{
	g_goMgr.DeleteGO(m_fade);
}

void GameClear::Update()
{
	//ゲームクリアの文字が落ちる。
	if (m_positionY < GAMECLEAR_POSITION_Y)
	{
		m_positionY += GAMECLEAR_MOVE_SPEED;
	}
	else if (m_fadeFlag == false) {
		m_fade = g_goMgr.NewGO<Fade>();
		m_fadeFlag = true;
	}
	else {
		//フェードアウト
		m_fade->StartFadeOut();
	}
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
