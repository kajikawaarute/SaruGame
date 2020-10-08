#include "stdafx.h"
#include "SkinModelRender.h"


SkinModelRender::SkinModelRender()
{
}

SkinModelRender::~SkinModelRender()
{
}

void SkinModelRender::Update()
{
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void SkinModelRender::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void SkinModelRender::Init(const wchar_t* filePath)
{
	m_model.Init(filePath);
}
