#pragma once
#include "IGameObject.h"

class PlayerHP : public IGameObject
{
public:
	PlayerHP();
	~PlayerHP();

	/// <summary>
	/// プレイヤーHPの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// プレイヤーHPの描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// ダメージフラグを設定
	/// </summary>
	/// <param name="flag"></param>
	/// <returns></returns>
	bool SetDamageFlag(bool flag)
	{
		return m_damageFlag = flag;
	}

	/// <summary>
	/// ゲームオーバーフラグを取得
	/// </summary>
	/// <returns></returns>
	bool GetGameOver()
	{
		return m_gameOverFlag;
	}
	/// <summary>
	/// スプライトバッチの描画関数
	/// </summary>
	void SpriteBatchDraw();
private:
	const int m_playerHP = 3;

	DirectX::SpriteBatch* m_spriteBatch;					//スプライトバッチ
	DirectX::FXMVECTOR color = DirectX::Colors::White;		//カラー。

	ID3D11Device* m_device[3];									//構築済み
	ID3D11DeviceContext* m_deviceContext[3];					//構築済み
	ID3D11ShaderResourceView* m_shaderResourceView[3];			//読み込んだ画像ファイルの保存先

	float m_positionX[3] = { 0.0f, 50.0f, 100.0f};		//X座標
	float m_positionY[3] = { 0.0f, 0.0f, 0.0f};			//Y座標
	float m_rotation[3] = {0.0f, 0.0f, 0.0f};			//画像の回転
	float m_scale[3] = { 0.1f, 0.1f, 0.1f};				//拡大率
	float m_depth[3] = { 0.0f, 0.0f, 0.0f};				//スプライトの深度

	bool m_damageFlag = false;		//攻撃を受けた時の判定フラグ
	bool m_muteki = false;			//無敵判定
	bool m_gameOverFlag = false;	//ゲームオーバーフラグ
	int m_mutekiTimer = 0;			//無敵時間
};

