#include "stdafx.h"
#include "BananaPeel.h"
#include "IGameObjectManager.h"
#include "Player.h"

const int DEATH_TIME = 60;		//バナナの皮が消えるタイム。
const int STOP_TIME = 30;		//バナナの皮が止まるタイム。
const float BANANAPEEL_SPEED_POWER = 10.0f;		//バナナの皮の滑る速度をあげる力。

BananaPeel::BananaPeel()
{
	m_model.Init(L"Assets/modelData/BananaPeel.cmo");

	//ゴーストオブジェクトの作成。
	m_ghost.CreateBox(m_position, m_rotation, m_ghostObjectScale);
}


BananaPeel::~BananaPeel()
{
}

void BananaPeel::Update()
{
	m_deathTimer++;
	//バナナの皮が消える。
	if (m_deathTimer == DEATH_TIME)
	{
		Delete();
	}

	//ゴーストオブジェクトの判定。
	g_physics.ContactTest(m_pl->GetcharaCon(), [&](const btCollisionObject& contactObject) {
		if (m_ghost.IsSelf(contactObject)) {
			Delete();
			m_pl->SetStateSliped();
		}
		});

	m_stopTimer++;
	//バナナの皮が滑っている。
	if (m_stopTimer < STOP_TIME)
	{
		m_position += m_moveSpeed * BANANAPEEL_SPEED_POWER;
	}
	m_ghost.SetPosition(m_position);

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void BananaPeel::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void BananaPeel::Delete()
{
	g_goMgr.DeleteGO(this);
	m_ghost.Release();
}
