#include "stdafx.h"
#include "GunEnemyBullet.h"
#include "IGameObjectManager.h"
#include "Player.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"


GunEnemyBullet::GunEnemyBullet()
{
	m_model.Init(L"Assets/modelData/GunEnemyBullet.cmo");

	//ゴーストオブジェクトを作成。
	m_ghostObject.CreateBox(m_position, m_rotation, { 10.0f, 50.0f, 10.0f });

	//シャドウレシーバーを設定。
	m_model.SetShadowReciever(true);
}


GunEnemyBullet::~GunEnemyBullet()
{
}

void GunEnemyBullet::Update()
{
	//弾速を設定
	m_position += m_moveSpeed * 30.0f;

	//ゴーストオブジェクトの判定
	g_physics.ContactTest(m_pl->GetcharaCon(), [&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject)) {
			Delete();
			m_pl->Attacked();
		}
		});

	m_deathTimer++;
	if (m_deathTimer == 20)
	{
		Delete();
	}

	m_ghostObject.SetPosition(m_position);

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
	m_ghostObject.Release();
}
