#pragma once
#include "IGameObject.h"

class Player;
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
	/// サルが捕まえられた時の処理
	/// </summary>
	void GetSaru();

	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
private:
	SkinModel m_model;									//スキンモデル
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	Animation m_animation;								//アニメーション
	AnimationClip m_animClip[2];						//アニメーションクリップ
	enum EnAnimationClip {
		enAnim_taiki,			//待機アニメーション
		enAnim_run,				//走りアニメーション
		enAnim_num				//アニメーションクリップの数
	};
	EnAnimationClip m_enAnimClip;
	Player* m_pl = nullptr;		//プレイヤーのインスタンス
};

