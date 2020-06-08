#pragma once
#include "IGameObject.h"

class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();
	
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// スプライトバッチの描画関数
	/// </summary>
	void SpriteBatchDraw();

	float GetPositionY()
	{
		return m_positionY;
	}
private:
	DirectX::SpriteBatch* m_spriteBatch;					//スプライトバッチ
	DirectX::FXMVECTOR color = DirectX::Colors::White;		//カラー。

	ID3D11Device* m_device;									//構築済み
	ID3D11DeviceContext* m_deviceContext;					//構築済み
	ID3D11ShaderResourceView* m_shaderResourceView;			//読み込んだ画像ファイルの保存先

	float m_positionX = 300.0f;			//画像のX座標
	float m_positionY = -200.0f;		//画像のY座標
	float m_rotation = 0.0f;			//画像の回転
	float m_scale = 0.5f;				//拡大率
	float m_depth = 0.0f;				//スプライトの深度
};

