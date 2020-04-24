#pragma once
#include "IGameObject.h"

class Game;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	/// <summary>
	/// タイトルの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// タイトルの描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// spriteBatchの描画関数
	/// </summary>
	void SpriteBatchDraw();
private:
	DirectX::SpriteBatch* m_spriteBatch;					//スプライトバッチ

	ID3D11Device* m_device[3];									//構築済み
	ID3D11DeviceContext* m_deviceContext[3];					//構築済み
	ID3D11ShaderResourceView* m_shaderResourceView[3];			//読み込んだ画像ファイルの保存先

	float m_positionX[3] = {0.0f, 0.0f, 0.0f};			//画像のX座標
	float m_positionY[3] = {0.0f, 0.0f, 0.0f};			//画像のY座標

	Game* m_game = nullptr;				//ゲームのインスタンス
};

