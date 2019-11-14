#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "IGameObjectManager.h"

Enemy::Enemy()
{
	m_model.Init(L"Assets/modelData/Enemy-kari.cmo");
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Move();
	if (g_pad[0].IsTrigger(enButtonB)) {
		g_goMgr.DeleteGO(this);
	}
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Enemy::Move()
{
	CVector3 eneFoward = CVector3::AxisZ();

	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toPlayerDir = m_pl->GetPos() - m_position;
	float toPlayerLen = toPlayerDir.Length();
	toPlayerDir.Normalize();

	float d = eneFoward.Dot(toPlayerDir);

	float angle = acos(d);

	if (fabsf(angle) < CMath::DegToRad(90.0f) && toPlayerLen < 500.0f)
	{
		m_moveSpeed = toPlayerDir;
	}
	else {
		m_moveSpeed = CVector3::Zero();
	}
	m_moveSpeed.Normalize();
	m_moveSpeed.x *= 5.0f;
	m_moveSpeed.z *= 5.0f;
	m_moveSpeed.y = 0.0f;
	m_position -= m_moveSpeed;

}

void Enemy::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
