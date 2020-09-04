#pragma once
#include "IGameObject.h"
#include "RenderTarget.h"

class ToonRender
{
private:
	ToonRender();
public:
	static ToonRender& GetInstance()
	{
		static ToonRender instance;
		return instance;
	}
	~ToonRender();
	
	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();

	/// <summary>
	/// �[�x�l���������ނ��߂̃p�X
	/// </summary>
	void ZPrepass();

	/// <summary>
	/// �g�D�[�������_�[��SRV���擾
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetToonRenderSRV()
	{
		return m_toonRenderRT.GetRenderTargetSRV();
	}

	/// <summary>
	/// �g�D�[�������_�[��o�^�B
	/// </summary>
	/// <param name="toonRender">�g�D�[�������_�[</param>
	void RegistToonRender(SkinModel* toonRender)
	{
		m_toonRender.push_back(toonRender);
	}
private:
	RenderTarget m_toonRenderRT;				//�[�x�l���o�͂���p�̃o�b�t�@
	std::vector<SkinModel* > m_toonRender;		//�g�D�[�������_�[�̔z��
};

