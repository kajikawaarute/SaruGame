#pragma once
#include "IGameObject.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"

class SkinModelRender : public IGameObject
{
public:
	SkinModelRender();
	~SkinModelRender();

	/// <summary>
	/// �X�L�����f�������_�[�̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �X�L�����f�������_�[�̕`��֐�
	/// </summary>
	void Draw();

	/// <summary>
	/// ���f���̏������B
	/// </summary>
	/// <param name="filePath">���f���̃t�@�C���p�X</param>
	void Init(const wchar_t* filePath);

	/// <summary>
	/// �V���h�E�L���X�^�[��ݒ�B
	/// �L���X�^�[�͉e�𗎂Ƃ����B
	/// </summary>
	void SetShadowCaster()
	{
		ShadowMap::GetInstance().RegistShadowCaster(&m_model);
	}

	/// <summary>
	/// �V���h�E���V�[�o�[��ݒ�B
	/// ���V�[�o�[�͉e�𗎂Ƃ���鑤�B
	/// </summary>
	void SetShadowReciever()
	{
		m_model.SetShadowReciever(true);
	}

	/// <summary>
	/// �g�D�[�������_�����O��ݒ�B
	/// </summary>
	void SetToonRender()
	{
		ToonRender::GetInstance().RegistToonRender(&m_model);
	}

	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <param name="scale">�g�嗦</param>
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// �X�L�����f�����擾�B
	/// </summary>
	/// <returns>�X�L�����f��</returns>
	SkinModel& GetSkinModel()
	{
		return m_model;
	}
private:
	SkinModel m_model;									//���f��
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
};

