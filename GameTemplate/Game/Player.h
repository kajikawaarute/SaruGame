#pragma once
#include "character/CharacterController.h"
#include "IGameObject.h"
#include "PhysicsGhostObject.h"
#include "PlayerStateWait.h"
#include "PlayerStateMove.h"
#include "PlayerStateSaruGet.h"
#include "PlayerStateAttacked.h"
#include "PlayerStateJump.h"
#include "PlayerStateSliped.h"
#include "PlayerStateAttack.h"

class Saru;
class Enemy;
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

	CQuaternion& GetRot()
	{
		return m_rotation;
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
	/// キャラクターコントローラーを取得
	/// </summary>
	/// <returns></returns>
	CharacterController& GetcharaCon()
	{
		return m_charaCon;
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
	void SetEnemy(Enemy* enemy)
	{
		m_enemys.push_back(enemy);
	}

	/// <summary>
	/// サルを消すときの処理
	/// </summary>
	/// <param name="saru"></param>
	void DeleteSaru(Saru* saru);

	/// <summary>
	/// エネミーを消す時の処理
	/// </summary>
	/// <param name="enemy"></param>
	void DeleteEnemy(Enemy* enemy);

	/// <summary>
	/// 攻撃されたときの処理
	/// </summary>
	void Attacked();

	/// <summary>
	/// バナナの皮で滑った時の処理
	/// </summary>
	void Sliped();

	/// <summary>
	/// ジャンプしている時の処理
	/// </summary>
	void Jump();

	/// <summary>
	/// サルを捕獲しようとしている処理
	/// </summary>
	void SaruGet();

	/// <summary>
	/// 攻撃しようとしている時の処理
	/// </summary>
	void AttackTry();

	/// <summary>
	/// 攻撃している時の処理
	/// </summary>
	void Attack();

	/// <summary>
	/// 状態を滑っている状態にする。
	/// </summary>
	void SetStateSliped()
	{
		m_enPlayerState = enState_sliped;
	}

	void SetPlayerWalkSE();

	int GetSaruCount()
	{
		return m_saruCount;
	}

	/// <summary>
	/// 待機状態中の処理
	/// </summary>
	void StateWait();

	/// <summary>
	/// 移動状態中の処理
	/// </summary>
	void StateMove();

	/// <summary>
	/// ジャンプ状態中の処理
	/// </summary>
	void StateJump();

	/// <summary>
	/// アニメーションの再生が終わったら待機状態に切り替える
	/// </summary>
	void ChangeStateWaitAnim();

	/// <summary>
	/// 地面についたときに待機状態に切り替える。
	/// </summary>
	void ChangeStateWaitIsOnGound();
	
private:
	friend class PlayerStateWait;
	friend class PlayerStateMove;
	friend class PlayerStateSaruGet;
	friend class PlayerStateJump;
	friend class PlayerStateSliped;
	friend class PlayerStateAttack;

	SkinModel m_model;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	CVector3 m_scale = CVector3::One();					//拡大率
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CharacterController m_charaCon;						//キャラクターコントローラー

	PhysicsGhostObject m_ghost;							//ゴーストオブジェクト
	enum EnAnimationClip {
		enAnim_wait,		//待機アニメーション
		enAnim_walk,		//歩きアニメーション
		enAnim_saruGet,		//サルの捕獲アニメーション
		enAnim_attacked,	//攻撃されたときのアニメーション
		enAnim_jump,		//ジャンプしている時のアニメーション
		enAnim_sliped,		//滑っている時のアニメーション
		enAnim_attack,		//攻撃アニメーション
		enAnim_num			//アニメーションクリップの数
	};
	Animation m_animation;								//アニメーション
	AnimationClip m_animationClip[enAnim_num];			//アニメーションクリップ
	EnAnimationClip m_enAnimClip;

	enum EnPlayerState {
		enState_wait,		//待機状態
		enState_walk,		//歩き状態
		enState_saruGet,	//サルを捕獲
		enState_attacked,	//攻撃された状態
		enState_Jump,		//ジャンプ状態
		enState_sliped,		//滑っている状態
		enState_attack,		//攻撃状態
	};
	EnPlayerState m_enPlayerState;

	IPlayerState* m_currentState = nullptr;		//現在のプレイヤーの状態
	PlayerStateWait m_playerStateWait;			//待機状態
	PlayerStateMove m_playerStateMove;			//移動状態
	PlayerStateSaruGet m_playerStateSaruGet;	//サルを捕獲
	PlayerStateAttacked m_playerStateAttacked;	//攻撃された状態
	PlayerStateJump m_playerStateJump;			//ジャンプ状態
	PlayerStateSliped m_playerStateSliped;		//滑っている状態
	PlayerStateAttack m_playerStateAttack;		//攻撃状態
	
	int m_saruCount = 0;					//サルを捕まえた数

	const float animTime = 0.2f;			//アニメーションの補間時間

	std::vector<Saru*> m_sarus;
	std::vector<Enemy*> m_enemys;
public:
	void ChangeState(EnPlayerState nextState);
};

