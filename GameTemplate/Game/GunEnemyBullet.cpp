#include "stdafx.h"
#include "GunEnemyBullet.h"
#include "IGameObjectManager.h"
#include "Player.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"

const float GUN_SPPED_POWER = 30.0f;		//弾の速度を速くする力。
const int DEATH_TIME = 20;					//弾が消えるタイム。

GunEnemyBullet::GunEnemyBullet()
{
	m_model.Init(L"Assets/modelData/GunEnemyBullet.cmo");

	//ゴーストオブジェクトを作成。
	m_ghostObject.CreateBox(m_position, m_rotation, m_ghostObjectScale);

	//シャドウレシーバーを設定。
	m_model.SetShadowReciever(true);
}


GunEnemyBullet::~GunEnemyBullet()
{
}

void GunEnemyBullet::Update()
{
	//弾速を設定。
	m_position += m_moveSpeed * GUN_SPPED_POWER;

	//ゴーストオブジェクトの判定。
	g_physics.ContactTest(m_pl->GetcharaCon(), [&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject)) {
			Delete();
			m_pl->Attacked();
		}
		});

	m_deathTimer++;
	//弾が消える。
	if (m_deathTimer == DEATH_TIME)
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
