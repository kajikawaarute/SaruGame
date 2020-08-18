#include "stdafx.h"
#include "Wall.h"
#include "graphics/ToonRender.h"

Wall::Wall()
{
	m_model.Init(L"Assets/modelData/wall.cmo");

	m_model.SetShadowReciever(true);
}


Wall::~Wall()
{
}

void Wall::Update()
{
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//�g�D�[�������_��ݒ�B
	ToonRender::GetInstance().RegistToonRender(&m_model);
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
