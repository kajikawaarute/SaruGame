#pragma once
#include "IGameObject.h"

class Sky : public IGameObject
{
public:
	Sky();
	~Sky();
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

	CVector3 m_position;
	CQuaternion m_rotation;
	CVector3 m_scale;
};

