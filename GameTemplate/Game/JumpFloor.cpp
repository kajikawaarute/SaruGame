#include "stdafx.h"
#include "JumpFloor.h"
#include "Player.h"

const float FLOOR_JUMP_POWER = 4000.0f;		//�W�����v��W�����v�p���[�B
JumpFloor::JumpFloor()
{
	m_model.Init(L"Assets/modelData/JumpFloor.cmo");

	m_ghost.CreateBox(m_position, m_rotation,{1300.0f, 50.0f, 700.0f});
}


JumpFloor::~JumpFloor()
{
	m_ghost.Release();
}

void JumpFloor::Update()
{
	g_physics.ContactTest(m_player->GetcharaCon(), [&](const btCollisionObject& contactObject) {
		if (m_ghost.IsSelf(contactObject)) {
			m_player->GetMoveSpd().y = FLOOR_JUMP_POWER;
		}
		});

	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void JumpFloor::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void JumpFloor::CreateStaticObject()
{
	m_static.CreateMeshObject(m_model, m_position, m_rotation);
}
