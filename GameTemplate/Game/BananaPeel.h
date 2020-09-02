#pragma once
#include "IGameObject.h"
#include "physics/PhysicsGhostObject.h"

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
	/// バナナの皮を消す時の処理
	/// </summary>
	void Delete();

	/// <summary>
	///	座標を設定
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	CVector3& GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// 移動速度を設定
	/// </summary>
	/// <param name="move"></param>
	void SetMoveSpd(CVector3 move)
	{
		m_moveSpeed += move;
	}

	/// <summary>
	/// 移動速度を取得
	/// </summary>
	/// <returns></returns>
	CVector3 GetMoveSpd()
	{
		return m_moveSpeed;
	}

	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	PhysicsGhostObject m_ghost;							//ゴーストオブジェクト
	Player* m_pl = nullptr;								//プレイヤーのインスタンス
	int m_deathTimer = 0;								//消えるまでのタイマー
	int m_stopTimer = 0;								//止まるまでのタイマー
};

