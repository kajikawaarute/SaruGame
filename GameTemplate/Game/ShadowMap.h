#pragma once
#include "RenderTarget.h"

class ShadowMap
{
private:
	ShadowMap();
public:
	static ShadowMap& GetInstance()
	{
		static ShadowMap instance;
		return instance;
	}
	~ShadowMap();
	/// <summary>
	/// �V���h�E�}�b�v���X�V
	/// </summary>
	void UpdateShadowMap(CVector3 lightCameraPos, CVector3 lightCameraTarget);

	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();

	/// <summary>
	/// �V���h�E�}�b�v�ɃV���h�E�L���X�^�[�������_�����O�B
	/// </summary>
	void RenderToShadowMap();

	/// <summary>
	/// �V���h�E�L���X�^�[��o�^�B
	/// </summary>
	/// <param name="shadowCaster">�V���h�E�L���X�^�[</param>
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}
private:
	CVector3 m_lightCameraPosition = CVector3::Zero();		//���C�g�J�����̎��_
	CVector3 m_lightCameraTarget = CVector3::Zero();		//���C�g�J�����̒����_
	CMatrix	 m_lightViewMatrix = CMatrix::Identity();		//���C�g�r���[�s��
	CMatrix  m_lightProjMatrix = CMatrix::Identity();		//���C�g�v���W�F�N�V�����s��
	RenderTarget m_shadowMapRT;								//�V���h�E�}�b�v��`�悷�郌���_�����O�^�[�Q�b�g�B
	std::vector<SkinModel* > m_shadowCasters;				//�V���h�E�L���X�^�[�̔z��
};