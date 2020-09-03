#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "SaruStateWait.h"
#include "SaruStateRun.h"
#include "SaruStateAttack.h"
#include "SaruStateGet.h"
#include "SaruStateStun.h"
#include "SaruStateFound.h"

class Player;
class BananaPeel;
class BikkuriMark;
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
	/// サルの走った時の処理
	/// </summary>
	void Run();

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
	/// 見つかった時の処理
	/// </summary>
	void Found();

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
	void SetPos(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// サルの回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
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

	/// <summary>
	/// プレイヤーのインスタンスを設定。
	/// </summary>
	/// <param name="player">プレイヤーのインスタンス</param>
	void SetPlayer(Player* player)
	{
		m_pl = player;
	}

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
	/// 見つかった状態に設定
	/// </summary>
	void ChangeStateFound()
	{
		m_enSaruState = enState_found;
	}

	/// <summary>
	/// 怯んだ状態に設定。
	/// </summary>
	void ChangeStateStun()
	{
		m_enSaruState = enState_stun;
	}

	/// <summary>
	/// 捕まえられた時に呼ばれる関数
	/// </summary>
	void Death();

	/// <summary>
	/// アニメーションの再生が終わったら待機状態に切り替える
	/// </summary>
	void ChangeStateWaitAnim();

	/// <summary>
	/// サルが捕まえられた時のサウンドを再生する
	/// </summary>
	void SaruGetSound();

	/// <summary>
	/// サルがプレイヤーに見つかった時のサウンドを再生する。
	/// </summary>
	void SaruFoundSound();

	/// <summary>
	/// 設定された座標をパスリストに登録
	/// </summary>
	/// <param name="m_pos"></param>
	void PushPathPosition(CVector3 m_pos)
	{
		m_pathList.push_back(m_pos);
	}
private:
	friend class SaruStateWait;
	friend class SaruStateRun;
	friend class SaruStateAttack;
	friend class SaruStateGet;
	friend class SaruStateStun;
	friend class SaruStateFound;

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
		enAnim_found,			//見つかった時のアニメーション
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
		enState_stun,				//ひるんだ状態
		enState_found				//見つかった状態
	};
	EnSaruState m_enSaruState;

	ISaruState* m_currentState = nullptr;	//現在のサルの状態
	SaruStateWait m_saruStateWait;			//待機状態
	SaruStateRun m_saruStateRun;			//走り状態
	SaruStateAttack m_saruStateAttack;		//攻撃状態
	SaruStateGet m_saruStateGet;			//捕獲状態
	SaruStateStun m_saruStateStun;			//怯み状態
	SaruStateFound m_saruStateFound;		//見つかった状態

	Player* m_pl = nullptr;					//プレイヤーのインスタンス
	BananaPeel* m_banaPeel = nullptr;		//バナナの皮のインスタンス
	BikkuriMark* m_bikkuriMark = nullptr;

	int m_waitTimer = 0;		//待機状態になるまでのタイマー
	int m_banaPeelTimer = 0;	//バナナの皮を投げるまでのタイマー
	int pathNum = 0;			//パスの番号
	float angle = 0.0f;

	std::vector<CVector3> m_pathList;		//パスのリスト

	const float m_animTime = 0.2f;			//アニメーションの補間時間

	Effekseer::Effect* m_saruGetEffekt = nullptr;		//捕まえられた時のエフェクト
	Effekseer::Effect* m_saruRunEffect = nullptr;		//走っている時のエフェクト
	Effekseer::Effect* m_saruDamegeEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;

public:
	/// <summary>
	/// 状態を切り替える処理。
	/// </summary>
	/// <param name="nextState">サルの状態</param>
	void ChangeState(EnSaruState nextState);
};

