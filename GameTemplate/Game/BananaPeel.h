#pragma once
#include "IGameObject.h"

class BananaPeel : public IGameObject
{
public:
	BananaPeel();
	~BananaPeel();
	void Update();
	void Draw();
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	int m_timer = 0;
};

