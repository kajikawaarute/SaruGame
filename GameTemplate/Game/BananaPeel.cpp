#include "stdafx.h"
#include "BananaPeel.h"


BananaPeel::BananaPeel()
{
	m_model.Init(L"Assets/modelData/BananaPeel.cmo");
}


BananaPeel::~BananaPeel()
{
}

void BananaPeel::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void BananaPeel::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
