#include "stdafx.h"
#include "BananaPeel.h"
#include "IGameObjectManager.h"
#include "Player.h"

const int DEATH_TIME = 60;		//バナナの皮が消えるタイム。
const int STOP_TIME = 30;		//バナナの皮が止まるタイム。
const float BANANAPEEL_SPEED_POWER = 10.0f;		//バナナの皮の滑る速度をあげる力。

BananaPeel::BananaPeel()
{
	//モデルの初期化。
	m_skinModel = g_goMgr.NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/BananaPeel.cmo");

	//ゴーストオブジェクトの作成。
	m_ghost.CreateBox(m_position, m_rotation, m_ghostObjectScale);

	//シャドウレシーバーを設定。
	m_skinModel->SetShadowReciever();
}


BananaPeel::~BananaPeel()
{
	//スキンモデルを削除。
	g_goMgr.DeleteGO(m_skinModel);
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

	//ゴーストオブジェクトの座標を設定。
	m_ghost.SetPosition(m_position);

	//シャドウキャスターを設定。
	m_skinModel->SetShadowCaster();

	//トゥーンレンダーを設定。
	m_skinModel->SetToonRender();

	//スキンモデルの座標を設定。
	m_skinModel->SetPosition(m_position);

	//スキンモデルの回転を設定。
	m_skinModel->SetRotation(m_rotation);
}

void BananaPeel::Delete()
{
	g_goMgr.DeleteGO(this);
	//スキンモデルを削除。
	g_goMgr.DeleteGO(m_skinModel);
}
