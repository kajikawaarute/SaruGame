#pragma once
#include "IGameObject.h"
#include "physics/PhysicsGhostObject.h"

class Player;
class GunEnemyBullet : public IGameObject
{
public:
	GunEnemyBullet();
	~GunEnemyBullet();

	/// <summary>
	/// ガンエネミーバレットの皮の更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// ガンエネミーバレットの描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// ガンエネミーバレットを消す時の処理
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

	/// <summary>
	/// プレイヤーのインスタンスを設定。
	/// </summary>
	/// <param name="player"></param>
	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
private:
	SkinModel m_model;										//モデル
	CVector3 m_position = CVector3::Zero();					//座標
	CVector3 m_moveSpeed = CVector3::Zero();				//移動速度
	CQuaternion m_rotation = CQuaternion::Identity();		//回転
	CVector3 m_scale = CVector3::One();						//拡大率
	CVector3 m_ghostObjectScale = { 50.0f, 50.0f, 50.0f };	//ゴーストオブジェクトの拡大率

	PhysicsGhostObject	m_ghostObject;					//ゴーストオブジェクト
	Player* m_pl = nullptr;								//プレイヤーのインスタンス
	int m_deathTimer = 0;								//消えるまでのタイマー
};

