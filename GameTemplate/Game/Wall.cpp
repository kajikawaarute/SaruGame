#include "stdafx.h"
#include "Wall.h"
#include "graphics/ToonRender.h"

Wall::Wall()
{
	//モデルの初期化。
	m_model.Init(L"Assets/modelData/wall.cmo");

	//シャドウレシーバーを設定。
	m_model.SetShadowReciever(true);
}


Wall::~Wall()
{
}

void Wall::Update()
{
	//トゥーンレンダを設定。
	ToonRender::GetInstance().RegistToonRender(&m_model);

	//ワールド行列の更新。
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
