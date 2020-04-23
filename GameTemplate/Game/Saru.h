#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

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
	/// サルからプレイヤーまでの距離
	/// </summary>
	void Distance();
private:
	SkinModel m_model;									//スキンモデル
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	Animation m_animation;								//アニメーション
	AnimationClip m_animClip[4];						//アニメーションクリップ
	enum EnAnimationClip {
		enAnim_taiki,			//待機アニメーション
		enAnim_run,				//走りアニメーション
		enAnim_attack,			//攻撃アニメーション
		enAnim_Get,				//捕獲アニメーション
		enAnim_num				//アニメーションクリップの数
	};
	enum EnSaruSaruState {
		enState_taiki,				//待機状態
		enState_run,				//走り状態
		enState_attack,				//攻撃状態
		enState_Get,				//捕獲状態
		enState_num					//状態の数
	};

	EnAnimationClip m_enAnimClip;
	EnSaruSaruState m_enSaruState;

	Player* m_pl = nullptr;					//プレイヤーのインスタンス
	BananaPeel* m_banaPeel = nullptr;		//バナナの皮のインスタンス

	int m_taikiTimer = 0;		//待機状態になるまでのタイマー
	int m_deathTimer = 0;		//捕獲されるまでのタイマー
	int m_banaPeelTimer = 0;		//バナナの皮を投げるまでのタイマー

	const float m_animTime = 0.2f;			//アニメーションの補間時間

	//Effekseerマネージャー管理
	Effekseer::Manager* m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_effekt = nullptr;		//エフェクト
	Effekseer::Handle m_playEffectHandle = -1;

	//CSoundSource m_saru_getAmiSE;			//捕獲されたときのSE
	//CSoundSource m_saru_attackSE;			//攻撃したときのSE
};

