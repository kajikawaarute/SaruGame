#pragma once
#include "Player.h"

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	/// <summary>
	/// ゲームカメラの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// プレイヤーのインスタンスを設定。
	/// </summary>
	/// <param name="player">プレイヤーのインスタンス</param>
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
private:
	Player* m_player = nullptr;		//プレイヤーのインスタンス
	CVector3 m_toCameraPos;			//カメラの座標
};