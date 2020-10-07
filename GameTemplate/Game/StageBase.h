#pragma once
#include "IGameObject.h"
#include "physics/PhysicsStaticObject.h"

/// <summary>
/// �X�e�[�W���Ƃɓ��ꏈ��������\�����l�����āA���N���X��p�ӁB 
/// </summary>
class StageBase : public IGameObject
{
public:
	StageBase();
	~StageBase();

	bool Start() override;

	 void Update() override;
	 /// <summary>
	 /// �X�e�[�W�ŗL�̍X�V�������L�q�B
	 /// </summary>
	 virtual void LocalUpdate() 
	 {

	 }
	 /// <summary>
	 /// .cmo�t�@�C���̃t�@�C���p�X���擾�B
	 /// </summary>
	 /// <returns></returns>
	 virtual const wchar_t* GetCMOFilePath() const = 0;

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
	 /// <param name="rot">��]</param>
	 void SetRotation(const CQuaternion rot)
	 {
		 m_rotation = rot;
	 }

private:
	SkinModelRender* m_skinModel = nullptr;				//�X�L�����f��

	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦

	PhysicsStaticObject m_staticObject;		//�ÓI�I�u�W�F�N�g
};

