#pragma once
#include "IGameObject.h"

class BikkuriMark : public IGameObject
{
public:
	BikkuriMark();
	~BikkuriMark();

	/// <summary>
	/// �r�b�N���}�[�N�̍X�V�֐��B
	/// </summary>
	void Update();

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
private:
	SkinModelRender* m_skinModel = nullptr;				//�X�L�����f��
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
};

