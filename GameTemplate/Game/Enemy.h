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
	/// エネミーの描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// エネミーの座標を取得
	/// </summary>
	/// <returns>座標</returns>
	CVector3& GetPos()
	{
		return m_position;
	}

	/// <summary>
	/// エネミーの移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// エネミーの回転処理
	/// </summary>
	void Turn();

	//エネミーの攻撃処理
	void Attack();
	
	/// <summary>
	/// 攻撃するまでの距離
	/// </summary>
	void AttackDistance();

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

	enum EnEnemyState {
		enState_taiki,			//待機状態
		enState_move,			//移動状態
		enState_attack,			//攻撃状態
	};
	EnEnemyState m_enEnemyState;

	Animation m_animation;					//アニメーション
	AnimationClip m_animationClip[1];		//アニメーションクリップ
	enum EnAnimationClip {
		enAnim_walk,						//歩きアニメーション
		enAnim_num							//アニメーションの数
	};
	EnAnimationClip m_enAnimClip;

	Player* m_pl = nullptr;					//プレイヤーのインスタンス
	
	int m_taikiTimer = 0;					//待機状態になるまでのタイマー
};

