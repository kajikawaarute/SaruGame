#include "stdafx.h"
#include "GunEnemyBullet.h"
#include "Player.h"

const float GUN_SPPED_POWER = 30.0f;		//弾の速度を速くする力。
const int DEATH_TIME = 20;					//弾が消えるタイム。

GunEnemyBullet::GunEnemyBullet()
{
	//モデルの初期化。
	m_skinModel = NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/GunEnemyBullet.cmo");

	//ゴーストオブジェクトを作成。
	m_ghostObject.CreateBox(m_position, m_rotation, m_ghostObjectScale);

	//シャドウレシーバーを設定。
	m_skinModel->SetShadowReciever();
}


GunEnemyBullet::~GunEnemyBullet()
{
	//スキンモデルを削除。
	DeleteGO(m_skinModel);
}

void GunEnemyBullet::Update()
{
	//弾速を設定。
	m_position += m_moveSpeed * GUN_SPPED_POWER;

	//ゴーストオブジェクトの判定。
	ContactTestPhysicsWorld(m_pl->GetcharaCon(), [&](const btCollisionObject& contactObject) {
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

	//ゴーストオブジェクトの座標を設定。
	m_ghostObject.SetPosition(m_position);

	//シャドウキャスターを設定。
	m_skinModel->SetShadowCaster();

	//トゥーンレンダーを設定。
	m_skinModel->SetToonRender();

	//スキンモデルの座標を設定。
	m_skinModel->SetPosition(m_position);

	//スキンモデルの回転を設定。
	m_skinModel->SetRotation(m_rotation);
}


void GunEnemyBullet::Delete()
{
	DeleteGO(this);
	//スキンモデルを削除。
	DeleteGO(m_skinModel);
}
