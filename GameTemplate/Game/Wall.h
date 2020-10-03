#pragma once
#include "IGameObject.h"
#include "physics/PhysicsStaticObject.h"

class Wall : public IGameObject
{
public:
	Wall();
	~Wall();

	/// <summary>
	/// 壁の更新関数。
	/// </summary>
	void Update();

	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// 回転を設定。
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// 静的オブジェクトの作成
	/// </summary>
	void CreateStaticObject();
private:
	SkinModelRender* m_skinModel = nullptr;				//スキンモデル
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率

	PhysicsStaticObject m_static;						//静的オブジェクト
};

