#include "stdafx.h"
#include "Saru.h"


Saru::Saru()
{
	m_model.Init(L"Assets/modelData/Saru.cmo");
	m_position.z = 500.0f;
}

Saru::~Saru()
{
}

void Saru::Update()
{
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Saru::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
