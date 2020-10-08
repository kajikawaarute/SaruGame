#pragma once

#include "physics/PhysicsStaticObject.h"
#include "physics/PhysicsGhostObject.h"
#include "character/CharacterController.h"

class Player;
class JumpFloor : public IGameObject
{
public:
	JumpFloor();
	~JumpFloor();
	/// <summary>
	/// シャンプ台の更新関数
	/// </summary>
	void Update();

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

	/// <summary>
	/// プレイヤーのインスタンスを設定。
	/// </summary>
	/// <param name="player"></param>
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
private:
	SkinModelRender* m_skinModel= nullptr;						//スキンモデル
	CVector3 m_position = CVector3::Zero();						//座標
	CQuaternion m_rotation = CQuaternion::Identity();			//回転
	CVector3 m_scale = CVector3::One();							//拡大率
	CVector3 m_ghostObjectScale = { 450.0f, 60.0f, 400.0f };	//ゴーストオブジェクトの拡大率

	PhysicsGhostObject m_ghost;							//ゴーストオブジェクト
	PhysicsStaticObject m_static;						//静的オブジェクト

	enum EnAnimationClip {
		enAnim_wait,		//ジャンプ台の待機アニメーション
		enAnim_jump,		//ジャンプ台アニメーション
		enAnim_num			//アニメーションクリップの数
	};

	Animation m_animation;								//アニメーション
	AnimationClip m_animationClip[enAnim_num];			//アニメーションクリップ
	EnAnimationClip m_enAnimClip;

	Player* m_player = nullptr;							//プレイヤーのインスタンス
};

