#pragma once
#include "IGameObject.h"

class Fade;
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();

	/// <summary>
	/// ゲームオーバーの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// ゲームオーバーの描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// SpriteBatchの描画関数
	/// </summary>
	void SpriteBatchDraw();
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

	Fade* m_fade = nullptr;				//フェードのインスタンス

	bool m_fadeFlag = false;			//フェードを行うかのフラグ
};

