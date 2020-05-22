#pragma once
#include "IGameObject.h"
#include "character/CharacterController.h"
#include "EnemyStateAttack.h"
#include "EnemyStateWait.h"
#include "EnemyStateMove.h"

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
	/// エネミーの座標を設定
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	CVector3& SetPos(CVector3 pos)
	{
		return m_position = pos;
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

	/// <summary>
	/// 倒されたときの処理
	/// </summary>
	void Delete();

	/// <summary>
	/// 待機タイマーを加算
	/// </summary>
	/// <returns></returns>
	int AddWaitTimer()
	{
		return m_waitTimer++;
	}
	/// <summary>
	/// 待機タイマーを取得
	/// </summary>
	/// <returns></returns>
	int GetWaitTimer()
	{
		return m_waitTimer;
	}
	/// <summary>
	/// 待機タイマーをリセット
	/// </summary>
	/// <returns></returns>
	int ReSetWaitTimer()
	{
		return m_waitTimer = 0;
	}

	/// <summary>
	/// 待機状態に切り替える
	/// </summary>
	void ChangeStateWait()
	{
		m_enEnemyState = enState_wait;
	}

	/// <summary>
	/// 移動状態に切り替える
	/// </summary>
	void ChangeStateMove()
	{
		m_enEnemyState = enState_move;
	}

	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
private:
	friend class EnemyStateWait;
	friend class EnemyStateMove;

	SkinModel m_model;									//スキンモデル
	CVector3 m_position = {0.0f, 0.0f, 300.0f};			//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度

	enum EnEnemyState {
		enState_wait,			//待機状態
		enState_move,			//移動状態
		enState_attack,			//攻撃状態
	};
	EnEnemyState m_enEnemyState;

	enum EnAnimationClip {
		enAnim_wait,						//待機アニメーション
		enAnim_walk,						//歩きアニメーション
		enAnim_num							//アニメーションの数
	};
	EnAnimationClip m_enAnimClip;

	Animation m_animation;							//アニメーション
	AnimationClip m_animationClip[enAnim_num];		//アニメーションクリップ
	const float m_animTime = 0.2f;					//アニメーションの補間時間


	Player* m_pl = nullptr;					//プレイヤーのインスタンス
	
	int m_waitTimer = 0;					//待機状態になるまでのタイマー

	IEnenyState* m_currentState = nullptr;	//現在のエネミーの状態
	EnemyStateAttack m_enemyStateAttack;	//攻撃状態
	EnemyStateWait m_enemyStateWait;		//待機状態
	EnemyStateMove m_enemyStateMove;		//移動状態

public:
	void ChangeState(EnEnemyState nextState);
};

