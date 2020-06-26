#pragma once
#include "IGameObject.h"
#include "physics/PhysicsStaticObject.h"
#include "level/Level.h"

class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	void Update();
	void Draw();
	void Setposition(const CVector3& pos)
	{
		m_position = pos;
	}
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();

	PhysicsStaticObject m_static;						//静的オブジェクト
};

