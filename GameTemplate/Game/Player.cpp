#include "stdafx.h"
#include "Player.h"
#include "IGameObjectManager.h"

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");

	//キャラクターコントローラーの初期化
	m_charaCon.Init(50.0f, 100.0f, m_position);

	m_ghost.CreateBox({1700.0f, 0.0f, -100.0f}, CQuaternion::Identity(), { 300.0f, 30.0f, 200.0f });
}


Player::~Player()
{
}

void Player::Update()
{
	Move();

	m_moveSpeed.y -= 100.0f;

	g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghost.IsSelf(contactObject) == true) {
			m_moveSpeed.y = 3000.0f;
		}
		});

	if (g_pad[0].IsTrigger(enButtonA))
	{
		m_moveSpeed.y = 1000.0f;
	}

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotetion, m_scale);
}

void Player::Move()
{

	m_moveSpeed.x = g_pad[0].GetLStickXF() * 1000.0f;
	m_moveSpeed.z = g_pad[0].GetLStickYF() * 1000.0f;
	
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
}

void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}