#pragma once
#include "IGameObject.h"
#include "physics/PhysicsStaticObject.h"
#include "level/Level.h"

class Stage : public IGameObject
{
public:
	Stage();
	~Stage();

	/// <summary>
	/// �X�e�[�W�̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �X�e�[�W�̕`��֐�
	/// </summary>
	void Draw();

	/// <summary>
	/// �X�e�[�W�̍��W��ݒ�B
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �X�e�[�W�̉�]��ݒ�B
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

	PhysicsStaticObject m_static;						//�ÓI�I�u�W�F�N�g
};

