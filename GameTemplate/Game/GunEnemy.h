#pragma once
#include "IGameObject.h"

class Player;
class GunEnemy : public IGameObject
{
public:
	GunEnemy();
	~GunEnemy();

	/// <summary>
	/// ガンエネミーの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// ガンエネミーの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ガンエネミーの座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	/// <returns></returns>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ガンエネミーの回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}

	void SetPlayer(Player* player)
	{
		m_player = player;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率

	Player* m_player = nullptr;					//プレイヤーのインスタンス
};

