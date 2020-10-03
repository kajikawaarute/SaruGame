#pragma once
#include "IGameObject.h"
#include "physics/PhysicsStaticObject.h"

class Wall : public IGameObject
{
public:
	Wall();
	~Wall();

	/// <summary>
	/// �ǂ̍X�V�֐��B
	/// </summary>
	void Update();

	/// <summary>
	/// ���W��ݒ�
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

	/// <summary>
	/// �ÓI�I�u�W�F�N�g�̍쐬
	/// </summary>
	void CreateStaticObject();
private:
	SkinModelRender* m_skinModel = nullptr;				//�X�L�����f��
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦

	PhysicsStaticObject m_static;						//�ÓI�I�u�W�F�N�g
};

