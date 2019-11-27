#pragma once
#include "IGameObject.h"
#include "character/CharacterController.h"

class Player;
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	/// <summary>
	/// エネミーの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// エネミーの移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// エネミーの描画関数
	/// </summary>
	void Draw();

	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
private:
	SkinModel m_model;									//スキンモデル
	CVector3 m_position = {0.0f, 0.0f, 300.0f};			//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	Player* m_pl = nullptr;								//プレイヤーのインスタンス
	Animation m_animation;								//アニメーション
	AnimationClip m_animationClip[1];					//アニメーションクリップ
	enum EnAnimation {
		enAnim_walk,									//歩きアニメーション
		enAnim_num										//アニメーションの数
	};

};

