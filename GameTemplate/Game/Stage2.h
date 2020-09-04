#pragma once
#include "IGameObject.h"
#include "physics/PhysicsStaticObject.h"

class Stage2 : public IGameObject
{
public:
	Stage2();
	~Stage2();

	/// <summary>
	/// �X�e�[�W2�̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �X�e�[�W2�̕`��֐�
	/// </summary>
	void Draw();

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ��]��ݒ�B
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

	PhysicsStaticObject m_staticObject;		//�ÓI�I�u�W�F�N�g
};

