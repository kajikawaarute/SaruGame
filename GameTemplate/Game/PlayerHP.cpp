#include "stdafx.h"
#include "IGameObjectManager.h"
#include "PlayerHP.h"

const float PLAYER_HP_SPRITE_SCALE = 0.005f;	//プレイヤーHPの拡大率
const float PLAYER_HP_SPRITE_SIZE = 0.001f;		//プレイヤーHPの大きさ

PlayerHP::PlayerHP()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();

	for (int i = 0; i < m_playerHP; i++) {
		//画像の読み込み。
		m_device[i] = g_graphicsEngine->GetDevice();
		DirectX::CreateDDSTextureFromFile(
			m_device[i],						//デバイス
			L"Assets/sprite/PlayerHP.dds",	//読み込む画像
			nullptr,
			&m_shaderResourceView[i]			//読み込んだファイルの情報を格納
		);
	}
}

PlayerHP::~PlayerHP()
{
}

void PlayerHP::Update()
{
	if (m_muteki) {
		m_mutekiTimer++;
		//無敵時間
		if (m_mutekiTimer > 30) {
			m_muteki = false;
			m_damageFlag = false;
			m_mutekiTimer = 0;
		}
	}

	if (!m_muteki) {
		if (m_damageFlag && m_scale[2] > PLAYER_HP_SPRITE_SIZE) {
			m_scale[2] -= PLAYER_HP_SPRITE_SCALE;
			if (m_scale[2] < PLAYER_HP_SPRITE_SIZE){
				m_muteki = true;
			}
		}
		else if (m_damageFlag && m_scale[1] > PLAYER_HP_SPRITE_SIZE) {
			m_scale[1] -= PLAYER_HP_SPRITE_SCALE;
			if (m_scale[1] < PLAYER_HP_SPRITE_SIZE) {
				m_muteki = true;
			}
		}
		else if (m_damageFlag && m_scale[0] > PLAYER_HP_SPRITE_SIZE) {
			m_scale[0] -= PLAYER_HP_SPRITE_SCALE;
			if (m_scale[0] < PLAYER_HP_SPRITE_SIZE) {
				m_gameOverFlag = true;
			}
		}
	}
}

void PlayerHP::Draw()
{
	SpriteBatchDraw();
}

void PlayerHP::SpriteBatchDraw()
{
	for (int i = 0; i < m_playerHP; i++) {
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
