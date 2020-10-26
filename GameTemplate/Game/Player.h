#pragma once
#include "character/CharacterController.h"

#include "PlayerStateWait.h"
#include "PlayerStateMove.h"
#include "PlayerStateSaruGet.h"
#include "PlayerStateAttacked.h"
#include "PlayerStateJump.h"
#include "PlayerStateSliped.h"
#include "PlayerStateAttack.h"
#include "PlayerStateDeath.h"

class Saru;
class Enemy;
class GunEnemy;
class PlayerHP;
class Player : public IGameObject
{
public:
	Player();
	~Player();

	/// <summary>
	/// プレイヤーのUpdate関数前に呼ばれる開始関数
	/// </summary>
	/// <returns>trueを返すと一度だけ呼ばれる</returns>
	bool Start();

	/// <summary>
	/// プレイヤーの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// プレイヤーの移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// プレイヤーの座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	void Setposition(const CVector3& pos)
	{
		m_position = pos;
		m_charaCon.SetPosition(m_position);
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
	/// プレイヤーの回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// プレイヤーの回転を取得
	/// </summary>
	/// <returns></returns>
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

	/// <summary>
	/// サルのインスタンスを設定。
	/// </summary>
	/// <param name="saru">サルのインスタンス</param>
	void SetSaru(Saru* saru)
	{
		m_sarus.push_back(saru);
	}

	/// <summary>
	/// エネミ－のインスタンスを取得。
	/// </summary>
	/// <param name="enemy">エネミ－のインスタンス</param>
	void SetEnemy(Enemy* enemy)
	{
		m_enemys.push_back(enemy);
	}

	/// <summary>
	/// ガンエネミーのインスタンスを設定。
	/// </summary>
	/// <param name="gunEnemy">ガンエネミーのインスタンス</param>
	void SetGunEnemy(GunEnemy* gunEnemy)
	{
		m_gunEnemys.push_back(gunEnemy);
	}

	/// <summary>
	/// プレイヤーHPのインスタンスを設定。
	/// </summary>
	/// <param name="playerHp">レイヤーHPのインスタンス</param>
	void SetPlayerHP(PlayerHP* playerHp)
	{
		m_playerHp = playerHp;
	}

	/// <summary>
	/// サルを消すときの処理
	/// </summary>
	/// <param name="saru">サルのインスタンス</param>
	void DeleteSaru(Saru* saru);

	/// <summary>
	/// エネミーを消す時の処理
	/// </summary>
	/// <param name="enemy">サルのインスタンス</param>
	void DeleteEnemy(Enemy* enemy);

	/// <summary>
	/// ガンエネミーを消す時の処理
	/// </summary>
	/// <param name="gunEnemy">ガンエネミーのインスタンス</param>
	void DeleteGunEnemy(GunEnemy* gunEnemy);

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
	/// 死亡しているときの状態にする。
	/// </summary>
	void StateDeath();

	/// <summary>
	/// 状態を滑っている状態にする。
	/// </summary>
	void SetStateSliped()
	{
		m_enPlayerState = enState_sliped;
	}

	/// <summary>
	/// 捕まえたサルカウントを取得。
	/// </summary>
	/// <returns>捕まえたサル</returns>
	const int& GetSaruCount()
	{
		return m_saruCount;
	}

	/// <summary>
	/// 倒したエネミーカウントを取得。
	/// </summary>
	/// <returns>倒したエネミー</returns>
	const int& GetEnemyCount()
	{
		return m_enemyCount;
	}

	/// <summary>
	/// アニメーションの再生が終わったら待機状態に切り替える
	/// </summary>
	void ChangeStateWaitAnim();

	/// <summary>
	/// 地面についたときに待機状態に切り替える。
	/// </summary>
	void ChangeStateWaitIsOnGound();
	/// <summary>
	/// 吹き飛ばしの力を設定する。
	/// </summary>
	/// <param name="attackedPower"></param>
	void SetAttackedPower(const CVector3& attackedPower)
	{
		m_attackedPower = attackedPower;
	}
private:
	friend class PlayerStateWait;
	friend class PlayerStateMove;
	friend class PlayerStateSaruGet;
	friend class PlayerStateJump;
	friend class PlayerStateSliped;
	friend class PlayerStateAttack;
	friend class PlayerStateDeath;
	friend class PlayerStateAttacked;

	SkinModelRender* m_skinModel = nullptr;				//スキンモデル									
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	CVector3 m_attackedPower = CVector3::Zero();		//攻撃を食らったときの吹き飛ばし力。
	CVector3 m_scale = CVector3::One();					//拡大率
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CharacterController m_charaCon;						//キャラクターコントローラー

	enum EnAnimationClip {
		enAnim_wait,		//待機アニメーション
		enAnim_walk,		//歩きアニメーション
		enAnim_saruGet,		//サルの捕獲アニメーション
		enAnim_attacked,	//攻撃されたときのアニメーション
		enAnim_jump,		//ジャンプしている時のアニメーション
		enAnim_sliped,		//滑っている時のアニメーション
		enAnim_attack,		//攻撃アニメーション
		enAnim_death,		//死亡アニメーション
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
		enState_death		//死亡状態
	};
	EnPlayerState m_enPlayerState = enState_wait;

	IPlayerState* m_currentState = nullptr;		//現在のプレイヤーの状態
	PlayerStateWait m_playerStateWait;			//待機状態
	PlayerStateMove m_playerStateMove;			//移動状態
	PlayerStateSaruGet m_playerStateSaruGet;	//サルを捕獲
	PlayerStateAttacked m_playerStateAttacked;	//攻撃された状態
	PlayerStateJump m_playerStateJump;			//ジャンプ状態
	PlayerStateSliped m_playerStateSliped;		//滑っている状態
	PlayerStateAttack m_playerStateAttack;		//攻撃状態
	PlayerStateDeath m_playerStateDeath;		//死亡状態
	
	int m_saruCount = 0;					//サルを捕まえた数
	int m_enemyCount = 0;					//エネミーを倒した数

	const float animTime = 0.2f;			//アニメーションの補間時間

	std::vector<Saru*> m_sarus;				//サルのリスト
	std::vector<Enemy*> m_enemys;			//エネミーのリスト
	std::vector<GunEnemy*> m_gunEnemys;		//ガンエネミーのリスト

	PlayerHP* m_playerHp = nullptr;			//プレイヤーHPのインスタンス

public:
	/// <summary>
	/// 状態を切り替える処理。
	/// </summary>
	/// <param name="nextState">プレイヤーの状態</param>
	void ChangeState(EnPlayerState nextState);
};

