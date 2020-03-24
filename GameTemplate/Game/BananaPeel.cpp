#include "stdafx.h"
#include "BananaPeel.h"
#include "IGameObjectManager.h"
#include "Player.h"

BananaPeel::BananaPeel()
{
	m_model.Init(L"Assets/modelData/BananaPeel.cmo");
	m_ghost.CreateBox(m_position, m_rotation, m_scale);
}


BananaPeel::~BananaPeel()
{
}

void BananaPeel::Update()
{
	if (g_pad[0].IsTrigger(enButtonX)){
		g_goMgr.DeleteGO(this);
		m_ghost.Release();
	}
	m_deathTimer++;
	if (m_deathTimer == 180)
	{
		g_goMgr.DeleteGO(this);
		m_ghost.Release();
	}

	g_physics.ContactTest(m_pl->GetcharaCon(), [&](const btCollisionObject& contactObject) {
		if (m_ghost.IsSelf(contactObject)) {
			m_pl->Slip();
		}
		});

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void BananaPeel::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
