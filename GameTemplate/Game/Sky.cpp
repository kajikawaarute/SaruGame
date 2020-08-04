#include "stdafx.h"
#include "Sky.h"

Sky::Sky()
{
	m_model.Init(L"Assets/modelData/SkyBox.cmo");
}

Sky::~Sky()
{
}

void Sky::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Sky::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
