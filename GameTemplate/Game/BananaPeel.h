#pragma once
#include "IGameObject.h"

class BananaPeel : public IGameObject
{
public:
	BananaPeel();
	~BananaPeel();
	void Update();
	void Draw();

private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();				//ç¿ïW
	CQuaternion m_rotation = CQuaternion::Identity();	//âÒì]
	CVector3 m_scale = CVector3::One();					//ägëÂó¶
};

