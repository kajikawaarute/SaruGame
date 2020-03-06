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
	m_timer++;
	if (m_timer == 180)
	{
		g_goMgr.DeleteGO(this);
		m_ghost.Release();
	}

	/*g_physics.ContactTest(m_pl->GetcharaCon(), [&](const btCollisionObject& contactObject) {
		if (m_ghost.IsSelf(contactObject) == true) {
			Slip(m_pl->GetRot());
		}
		});*/

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void BananaPeel::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
