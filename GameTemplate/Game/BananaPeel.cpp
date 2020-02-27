#include "stdafx.h"
#include "BananaPeel.h"
#include "IGameObjectManager.h"

BananaPeel::BananaPeel()
{
	m_model.Init(L"Assets/modelData/BananaPeel.cmo");
}


BananaPeel::~BananaPeel()
{
}

void BananaPeel::Update()
{
	if (g_pad[0].IsTrigger(enButtonX)){
		g_goMgr.DeleteGO(this);
	}
	m_timer++;
	if (m_timer == 180)
	{
		g_goMgr.DeleteGO(this);
	}

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void BananaPeel::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
