#include "stdafx.h"
#include "GunEnemy.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"

GunEnemy::GunEnemy()
{
	m_model.Init(L"Assets/modelData/GunEnemy.cmo");

	//シャドウレシーバーを設定。
	m_model.SetShadowReciever(true);
}

GunEnemy::~GunEnemy()
{
}

void GunEnemy::Update()
{
	//シャドウキャスターを設定。
	ShadowMap::GetInstance().RegistShadowCaster(&m_model);

	//トゥーンレンダーを設定。
	ToonRender::GetInstance().RegistToonRender(&m_model);

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void GunEnemy::Draw()
{
	m_model.Draw(
		enRenderMode_Normal, 
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}
