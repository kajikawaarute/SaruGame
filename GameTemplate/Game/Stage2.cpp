#include "stdafx.h"
#include "Stage2.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"

Stage2::Stage2()
{
	//���f���̏������B
	m_model.Init(L"Assets/modelData/stage_02.cmo");

	//�ÓI�I�u�W�F�N�g���쐬�B
	m_staticObject.CreateMeshObject(m_model, m_position, m_rotation);

	//�V���h�E���V�[�o�[��ݒ�B
	m_model.SetShadowReciever(true);
}

Stage2::~Stage2()
{
}

void Stage2::Update()
{
	//�V���h�E�L���X�^�[��ݒ�B
	ShadowMap::GetInstance().RegistShadowCaster(&m_model);

	//�g�D�[�������_�[��ݒ�B
	ToonRender::GetInstance().RegistToonRender(&m_model);

	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Stage2::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
