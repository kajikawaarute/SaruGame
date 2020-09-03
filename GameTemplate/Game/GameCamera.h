#pragma once
#include "IGameObject.h"
#include "Player.h"
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	void Update();
	void Draw();

	/// <summary>
	/// プレイヤーのインスタンスを設定。
	/// </summary>
	/// <param name="player">プレイヤーのインスタンス</param>
	void SetPlayer(Player* player)
	{
		pl = player;
	}
private:
	Player* pl = nullptr;		//プレイヤーのインスタンス
	CVector3 m_toCameraPos;		//カメラの座標
};

