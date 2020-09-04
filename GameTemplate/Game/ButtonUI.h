#pragma once
#include "IGameObject.h"

class ButtonUI : public IGameObject
{
public:
	ButtonUI();
	~ButtonUI();

	/// <summary>
	/// ButtonUIの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// ButtonUIの描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// SpriteBatchの描画関数
	/// </summary>
	void SpriteBatch();
private:
	DirectX::SpriteBatch* m_spriteBatch;					//スプライトバッチ
	DirectX::FXMVECTOR color = DirectX::Colors::White;		//カラー。

	ID3D11Device* m_device;									//構築済み
	ID3D11DeviceContext* m_deviceContext;					//構築済み
	ID3D11ShaderResourceView* m_shaderResourceView;			//読み込んだ画像ファイルの保存先

	float m_positionX = 800.0f;		//画像のX座標
	float m_positionY = 420.0f;		//画像のY座標
	float m_rotation = 0.0f;		//画像の回転
	float m_scale = 0.5f;			//拡大率
	float m_depth = 0.0f;			//スプライトの深度
};

