#pragma once
#include "character/CharacterController.h"
#include "IGameObject.h"
#include "PhysicsGhostObject.h"

class Saru;
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

	/// <summary>
	/// プレイヤーの移動速度を取得
	/// </summary>
	/// <returns></returns>
	CVector3& GetMoveSpd()
	{
		return m_moveSpeed;
	}
	/// <summary>
	/// サルを捕まえた時の処理
	/// </summary>
	void GetSaru();

	/// <summary>
	/// プレイヤーの回転処理
	/// </summary>
	void Turn();

	void SetSaru(Saru* saru)
	{
		m_sarus.push_back(saru);
	}

	/// <summary>
	/// サルを消すときの処理
	/// </summary>
	/// <param name="saru"></param>
	void DeleteSaru(Saru* saru);

	/// <summary>
	/// 攻撃されたときの処理
	/// </summary>
	void Attacked();

	CharacterController GetcharaCon()
	{
		return m_charaCon;
	}

	CQuaternion GetRot()
	{
		return m_rotation;
	}
private:
	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	CVector3 m_scale = CVector3::One();					//拡大率
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CharacterController m_charaCon;						//キャラクターコントローラー

	PhysicsGhostObject m_ghost;							//ゴーストオブジェクト
	Animation m_animation;								//アニメーション
	AnimationClip m_animationClip[3];					//アニメーションクリップ
	enum EnAnimationClip {
		enAnim_taiki,		//待機アニメーション
		enAnim_walk,		//歩きアニメーション
		enAnim_saruGet,		//サルの捕獲アニメーション
		enAnim_num			//アニメーションクリップの数
	};
	enum EnPlayerState {
		enState_taiki,		//待機状態
		enState_walk,		//歩き状態
		enState_saruGet,	//サルを捕獲
		enState_attacked,	//攻撃された状態
		enState_num			//状態の数
	};
	EnAnimationClip m_enAnimClip;

	EnPlayerState m_enPlayerState;
	int m_saruGet_taikiTimer = 0;			//捕獲状態から待機状態になるまでのタイマー
	int m_attacked_taikiTimer = 0;			//攻撃された状態から待機状態になるまでのタイマー

	std::vector<Saru*> m_sarus;
};

