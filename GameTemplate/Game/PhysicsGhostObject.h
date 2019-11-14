#pragma once
#include "BoxCollider.h"

class PhysicsGhostObject
{
public:
	PhysicsGhostObject();
	~PhysicsGhostObject();

	void CreateBox(CVector3 pos, CQuaternion rot, CVector3 size);

	void Release();

	/// <summary>
	/// �S�[�X�g�쐬�����̋��ʏ���
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	void CreateCommon(CVector3 pos, CQuaternion rot);

	/// <summary>
	/// �����œn���ꂽ�S�[�X�g�I�u�W�F�N�g���������g������
	/// </summary>
	/// <param name="ghost">�S�[�X�g�I�u�W�F�N�g</param>
	/// <returns></returns>
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}
private:

	bool m_isRegistPhysicsWorld = false;	//�������[���h�ɓo�^���Ă��邩�̂ǂ����̃t���O
	btGhostObject m_ghostObject;			//�S�[�X�g

	std::unique_ptr<ICollider> m_collider;	//�R���C�_�[
};

