#pragma once
#include "IGameObject.h"

class Saru : public IGameObject
{
public:
	Saru();
	~Saru();
	void Update();
	void Draw();
private:
	SkinModel m_model;									//スキンモデル
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	Animation m_animation;								//アニメーション
	AnimationClip m_animClip[1];						//アニメーションクリップ
	enum EnAnimationClip {
		enAnim_taiki,			//待機アニメーション
		enAnim_num				//アニメーションクリップの数
	};
};

