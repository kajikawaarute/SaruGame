#include "stdafx.h"
#include "GunEnemy.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"

GunEnemy::GunEnemy()
{
	m_model.Init(L"Assets/modelData/GunEnemy.cmo");

	//�V���h�E���V�[�o�[��ݒ�B
	m_model.SetShadowReciever(true);
}

GunEnemy::~GunEnemy()
{
}

void GunEnemy::Update()
{
	//�V���h�E�L���X�^�[��ݒ�B
	ShadowMap::GetInstance().RegistShadowCaster(&m_model);

	//�g�D�[�������_�[��ݒ�B
	ToonRender::GetInstance().RegistToonRender(&m_model);

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void GunEnemy::Draw()
{
	m_model.Draw(
		enRenderMode_Normal, 
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}
