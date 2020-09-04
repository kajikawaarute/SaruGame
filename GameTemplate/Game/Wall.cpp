#include "stdafx.h"
#include "Wall.h"
#include "graphics/ToonRender.h"

Wall::Wall()
{
	//���f���̏������B
	m_model.Init(L"Assets/modelData/wall.cmo");

	//�V���h�E���V�[�o�[��ݒ�B
	m_model.SetShadowReciever(true);
}


Wall::~Wall()
{
}

void Wall::Update()
{
	//�g�D�[�������_��ݒ�B
	ToonRender::GetInstance().RegistToonRender(&m_model);

	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Wall::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Wall::CreateStaticObject()
{
	m_static.CreateMeshObject(m_model, m_position, m_rotation);
}
