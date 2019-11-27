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
	SkinModel m_model;									//�X�L�����f��
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x

};

