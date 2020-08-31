#include "stdafx.h"
#include "GunEnemyBullet.h"
#include "IGameObjectManager.h"
#include "Player.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"


GunEnemyBullet::GunEnemyBullet()
{
	m_model.Init(L"Assets/modelData/GunEnemyBullet.cmo");
}


GunEnemyBullet::~GunEnemyBullet()
{
}

void GunEnemyBullet::Update()
{
	m_position.y = 570.0f;
	m_position += m_moveSpeed * 30.0f;

	m_deathTimer++;
	if (m_deathTimer == 20)
	{
		Delete();
	}

	//シャドウレシーバーを設定。
	ShadowMap::GetInstance().RegistShadowCaster(&m_model);

	//トゥーンレンダーを設定。
	ToonRender::GetInstance().RegistToonRender(&m_model);

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void GunEnemyBullet::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void GunEnemyBullet::Delete()
{
	g_goMgr.DeleteGO(this);
}
