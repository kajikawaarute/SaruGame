#pragma once
#include "IGameObject.h"

class Sky : public IGameObject
{
public:
	Sky();
	~Sky();
	void Update();
	void Draw();

	/// <summary>
	/// ��̍��W��ݒ�
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ��̉�]��ݒ�
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}
private:
	SkinModel m_model;									//���f��

	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
};

