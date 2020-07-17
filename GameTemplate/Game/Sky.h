#pragma once
#include "IGameObject.h"

class Sky : public IGameObject
{
public:
	Sky();
	~Sky();
	void Update();
	void Draw();
private:
	SkinModel m_model;

	CVector3 m_position;
	CQuaternion m_rotation;
	CVector3 m_scale;
};

