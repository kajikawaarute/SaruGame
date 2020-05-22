#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "SaruStateWait.h"
#include "SaruStateRun.h"
#include "SaruStateAttack.h"
#include "SaruStateGet.h"
#include "SaruStateStun.h"

class Player;
class BananaPeel;
class Saru : public IGameObject
{
public:
	Saru();
	~Saru();
	/// <summary>
	/// サルの更新関数
	/// </summary>
	void Update();
	/// <summary>
	/// サルの移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// サルの描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// サルが捕まえられた時の処理
	/// </summary>
	void GetSaru();

	/// <summary>
	/// サルの攻撃処理
	/// </summary>
	void Attack();

	/// <summary>
	/// サルの回転処理
	/// </summary>
	void Turn();

	/// <summary>
	/// バナナの皮を投げる時の処理
	/// </summary>
	void BanaPeelThrow();

	/// <summary>
	/// ひるんだ時の処理
	/// </summary>
	void Stun();

	/// <summary>
	/// サルの座標を取得
	/// </summary>
	/// <returns></returns>
	CVector3& GetPos()
	{
		return m_position;
	}

	/// <summary>
	/// サルの座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	/// <returns></returns>
	CVector3& SetPos(CVector3 pos)
	{
		return m_position = pos;
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
	/// 待機タイマーを加算
	/// </summary>
	/// <returns></returns>
	int AddWaitTimer()
	{
		return m_waitTimer++;
	}

	/// <summary>
	/// 待機タイマーをリセット
	/// </summary>
	/// <returns></returns>
	int ReSetWaitTimer()
	{
		return m_waitTimer = 0;
	}

	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
	/// <summary>
	/// Effekserの初期化
	/// </summary>
	void InitEffekseer();
	/// <summary>
	/// Effekseerカメラ
	/// </summary>
	void EffekseerCamera();

	/// <summary>
	/// 攻撃するまでの距離
	/// </summary>
	void AttackDistance();

	/// <summary>
	/// 待機状態に設定
	/// </summary>
	void ChangeStateWait()
	{
		m_enSaruState = enState_wait;
	}

	/// <summary>
	/// 走り状態に設定
	/// </summary>
	void ChangeStateRun()
	{
		m_enSaruState = enState_run;
	}

	/// <summary>
	/// 捕まえられた時に呼ばれる関数
	/// </summary>
	void Death();

	/// <summary>
	/// アニメーションの再生が終わったら待機状態に切り替える
	/// </summary>
	void ChangeStateWaitAnim();
private:
	friend class SaruStateWait;
	friend class SaruStateRun;
	friend class SaruStateGet;
	friend class SaruStateStun;

	SkinModel m_model;									//スキンモデル
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	
	enum EnAnimationClip {
		enAnim_wait,			//待機アニメーション
		enAnim_run,				//走りアニメーション
		enAnim_attack,			//攻撃アニメーション
		enAnim_Get,				//捕獲アニメーション
		enAnim_stun,			//ひるんでいるアニメーション
		enAnim_num				//アニメーションクリップの数
	};
	Animation m_animation;								//アニメーション
	AnimationClip m_animClip[enAnim_num];				//アニメーションクリップ
	EnAnimationClip m_enAnimClip;

	enum EnSaruState {
		enState_wait,				//待機状態
		enState_run,				//走り状態
		enState_attack,				//攻撃状態
		enState_Get,				//捕獲状態
		enState_stun				//ひるんだ状態
	};
	EnSaruState m_enSaruState;

	ISaruState* m_currentState = nullptr;	//現在のサルの状態
	SaruStateWait m_saruStateWait;			//待機状態
	SaruStateRun m_saruStateRun;			//走り状態
	SaruStateAttack m_saruStateAttack;		//攻撃状態
	SaruStateGet m_saruStateGet;			//捕獲状態
	SaruStateStun m_saruStateStun;			//怯み状態

	Player* m_pl = nullptr;					//プレイヤーのインスタンス
	BananaPeel* m_banaPeel = nullptr;		//バナナの皮のインスタンス

	int m_waitTimer = 0;		//待機状態になるまでのタイマー
	int m_deathTimer = 0;		//捕獲されるまでのタイマー
	int m_banaPeelTimer = 0;	//バナナの皮を投げるまでのタイマー
	int m_stunTimer = 0;

	const float m_animTime = 0.2f;			//アニメーションの補間時間

	//Effekseerマネージャー管理
	Effekseer::Manager* m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_effekt = nullptr;		//エフェクト
	Effekseer::Handle m_playEffectHandle = -1;

	//CSoundSource m_saru_getAmiSE;			//捕獲されたときのSE
	//CSoundSource m_saru_attackSE;			//攻撃したときのSE
public:
	void ChangeState(EnSaruState nextState);
};

