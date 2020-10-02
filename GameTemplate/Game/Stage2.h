#pragma once
#include "IGameObject.h"
#include "physics/PhysicsStaticObject.h"

class Stage2 : public IGameObject
{
public:
	Stage2();
	~Stage2();

	/// <summary>
	/// ステージ2の更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 座標を設定。
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// 回転を設定。
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}
private:
	SkinModelRender* m_skinModel = nullptr;				//スキンモデル

	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率

	PhysicsStaticObject m_staticObject;		//静的オブジェクト
};

