#pragma once
#include "IGameObject.h"
#include "physics/PhysicsStaticObject.h"
#include "PhysicsGhostObject.h"
#include "character/CharacterController.h"

class Player;
class JumpFloor : public IGameObject
{
public:
	JumpFloor();
	~JumpFloor();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ゴーストオブジェクトの座標を設定
	/// </summary>
	/// <param name="pos">ゴーストオブジェクトの座標</param>
	void SetPositonGhost(const CVector3 pos)
	{
		m_ghost.SetPosition(pos);
	}

	/// <summary>
	/// 静的オブジェクトの作成
	/// </summary>
	void CreateStaticObject();

	void SetPlayer(Player* player)
	{
		m_player = player;
	}
private:
	SkinModel m_model;										//スキンモデル
	CVector3 m_position = CVector3::Zero();					//座標
	CQuaternion m_rotation = CQuaternion::Identity();		//回転
	CVector3 m_scale = CVector3::One();						//拡大率

	PhysicsGhostObject m_ghost;							//ゴーストオブジェクト
	PhysicsStaticObject m_static;						//静的オブジェクト

	Player* m_player = nullptr;							//プレイヤーのインスタンス
};

