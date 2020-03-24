#pragma once
#include "IGameObject.h"
#include "PhysicsGhostObject.h"

class Player;
class BananaPeel : public IGameObject
{
public:
	BananaPeel();
	~BananaPeel();

	/// <summary>
	/// バナナの皮の更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// バナナの皮の描画関数
	/// </summary>
	void Draw();

	/// <summary>
	///	座標を設定
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	int m_deathTimer = 0;								//消えるまでのカウント
	PhysicsGhostObject m_ghost;							//ゴーストオブジェクト
	Player* m_pl = nullptr;								//プレイヤーのインスタンス
};

