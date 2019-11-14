#pragma once
#include "IGameObject.h"

class GetAmi : public IGameObject
{
public:
	GetAmi();
	~GetAmi();
	void Update();
	void Draw();
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 m_scale = CVector3::One();
};

