#include "stdafx.h"
#include "Stage2.h"


Stage2::Stage2()
{
	m_model.Init(L"Assets/modelData/stage_02.cmo");
	m_staticObject.CreateMeshObject(m_model, m_position, m_rotation);
}

Stage2::~Stage2()
{
}

void Stage2::Update()
{
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
