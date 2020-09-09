#pragma once
#include "IGameObject.h"

class Game;
class Fade;
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
	Game* m_game = nullptr;				//ゲームのインスタンス
	Fade* m_fade = nullptr;

	DirectX::SpriteBatch* m_spriteBatch;					//スプライトバッチ
	DirectX::FXMVECTOR color = DirectX::Colors::White;		//カラー。

	ID3D11Device* m_device[3];									//構築済み
	ID3D11DeviceContext* m_deviceContext[3];					//構築済み
	ID3D11ShaderResourceView* m_shaderResourceView[3];			//読み込んだ画像ファイルの保存先

	float m_positionX[3] = {0.0f, 0.0f, 0.0f};			//画像のX座標
	float m_positionY[3] = {0.0f, 0.0f, 0.0f};			//画像のY座標
	float m_rotation[3] = { 0.0f, 0.0f, 0.0f };			//画像の回転
	float m_scale[3] = { 1.0f, 1.0f, 1.0f };			//拡大率
	float m_depth[3] = { 0.0f, 0.0f, 0.0f };			//スプライトの深度

	int m_gameStartTimer = 0;		//ゲームを始めるタイマー
	bool m_startFlag = false;		//ゲームを始めるフラグ
};

