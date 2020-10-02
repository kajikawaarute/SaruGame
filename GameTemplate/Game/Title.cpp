#include "stdafx.h"
#include "Title.h"
#include "IGameObjectManager.h"
#include "Game.h"
#include "Fade.h"

const float TITLE_POSITION_X = 50.0f;	//タイトル文字の座標X
const float TITLE_POSITION_Y = 10.0f;	//タイトル文字の座標Y
const int TITLE_GAME_START_TIME = 60;	//ゲームを開始するタイム

Title::Title()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();

	for (int i = 0; i < 3; i++)
	{
		m_device[i] = g_graphicsEngine->GetDevice();
	}

	//タイトル画像の読み込み
	DirectX::CreateDDSTextureFromFile(
		m_device[0],							//デバイス
		L"Assets/sprite/Title.dds",				//読み込む画像ファイル
		nullptr,
		&m_shaderResourceView[0]				//読み込んだファイルの情報を格納
	);

	//タイトル名の画像の読み込み
	DirectX::CreateDDSTextureFromFile(
		m_device[1],							//デバイス
		L"Assets/sprite/Catch_the_monkey.dds",	//読み込む画像ファイル
		nullptr,
		&m_shaderResourceView[1]				//読み込んだファイルの情報を格納
	);
	m_positionX[1] = -1500.0f;

	//Press_Start_Buttonの画像の読み込み
	DirectX::CreateDDSTextureFromFile(
		m_device[2],							//デバイス
		L"Assets/sprite/Press_Start.dds",		//読み込む画像ファイル
		nullptr,
		&m_shaderResourceView[2]				//読み込んだファイルの情報を格納
	);
	m_positionY[2] = 300.0f;
}


Title::~Title()
{
	g_goMgr.DeleteGO(m_fade);
}

void Title::Update()
{
	if (g_pad[0].IsTrigger(enButtonStart) && m_startFlag == false && m_positionX[1] == 0.0f && m_positionY[2] == 0.0f)
	{
		m_fade = g_goMgr.NewGO<Fade>();
		m_startFlag = true;
	}
	if (m_startFlag == true) {
		m_gameStartTimer++;
		m_fade->StartFadeOut();
		if (m_gameStartTimer > TITLE_GAME_START_TIME) {
			Game::stageNo = 0;
			m_game = g_goMgr.NewGO<Game>();
			g_goMgr.DeleteGO(this);
		}
	}
	if (m_positionX[1] < 0.0f) {
		m_positionX[1] += TITLE_POSITION_X;
	}
	if (m_positionY[2] > 0.0f) {
		m_positionY[2] -= TITLE_POSITION_Y;
	}
	
}

void Title::Draw()
{
	SpriteBatchDraw();
}

void Title::SpriteBatchDraw()
{
	for (int i = 0; i < 3; i++)
	{
		m_spriteBatch->Begin();
		m_spriteBatch->Draw(
			m_shaderResourceView[i],							//読み込んだ画像ファイル
			DirectX::XMFLOAT2(m_positionX[i], m_positionY[i]),	//画像の座標
			nullptr,											//スプライトを任意の領域に表示
			color,												//カラー
			m_rotation[i],										//回転角度
			DirectX::XMFLOAT2(0.0f, 0.0f),						//回転軸の位置
			m_scale[i],											//拡大率
			DirectX::SpriteEffects::SpriteEffects_None,			//スプライトの表示反転
			m_depth[i]											//スプライトの深度を指定
		);
		m_spriteBatch->End();
	}


}
