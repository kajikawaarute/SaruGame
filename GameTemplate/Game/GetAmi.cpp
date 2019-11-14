#include "stdafx.h"
#include "GetAmi.h"


GetAmi::GetAmi()
{
	m_model.Init(L"Assets/modelData/GetAmi.cmo");
}


GetAmi::~GetAmi()
{
}

void GetAmi::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void GetAmi::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
