#pragma once
#include "IGameObject.h"

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
	/// サルが捕まえられた時の処理
	/// </summary>
	void GetSaru();

	/// <summary>
	/// サルの回転処理
	/// </summary>
	void Turn();

	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
	/// <summary>
	/// Effekserの初期化
	/// </summary>
	void InitEffekseer();

	void EffekseerCamera();

	void Angle();
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
		enSaru_taiki,			//待機状態
		enSaru_run,				//走り状態
		enSaru_attack,			//攻撃状態
		enSaru_Get,				//捕獲状態
		enSaru_num				//状態の数
	};

	EnAnimationClip m_enAnimClip;
	EnSaruSaruState m_enSaruState;

	Player* m_pl = nullptr;		//プレイヤーのインスタンス
	int m_timer = 0;
	int m_deathTimer = 0;
	int m_bananaCount = 0;

	//Effekseerマネージャー管理
	Effekseer::Manager* m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_effekt = nullptr;		//エフェクト
	Effekseer::Handle m_playEffectHandle = -1;
};

