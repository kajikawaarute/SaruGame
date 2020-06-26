#include "stdafx.h"
#include "BikkuriMark.h"
#include "IGameObjectManager.h"

BikkuriMark::BikkuriMark()
{
	m_model.Init(L"Assets/modelData/Bikkuri_Mark.cmo");
}


BikkuriMark::~BikkuriMark()
{
}

void BikkuriMark::Update()
{
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void BikkuriMark::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
