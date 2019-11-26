#pragma once
#include "character/CharacterController.h"
#include "IGameObject.h"
#include "PhysicsGhostObject.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	/// <summary>
	/// プレイヤーの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// プレイヤーの移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// プレイヤーの描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤーの座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	void Setposition(const CVector3& pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// プレイヤーの座標を取得
	/// </summary>
	/// <returns></returns>
	CVector3& GetPos()
	{
		return m_position;
	}
private:
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	CVector3 m_scale = CVector3::One();					//拡大率
	CQuaternion m_rotetion = CQuaternion::Identity();	//回転
	CharacterController m_charaCon;						//キャラクターコントローラー

	PhysicsGhostObject m_ghost;							//ゴーストオブジェクト
	Animation m_animation;								//アニメーション
	AnimationClip m_animationClip[2];					//アニメーションクリップ
	enum EnAnimationClip {
		enAnim_walk,		//歩きアニメーション
		enAnim_taiki,		//待機アニメーション
		enAnim_num			//アニメーションクリップの数
	};
};

