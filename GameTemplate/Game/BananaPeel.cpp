#include "stdafx.h"
#include "BananaPeel.h"
#include "IGameObjectManager.h"
#include "Player.h"

const int DEATH_TIME = 60;		//�o�i�i�̔炪������^�C���B
const int STOP_TIME = 30;		//�o�i�i�̔炪�~�܂�^�C���B
const float BANANAPEEL_SPEED_POWER = 10.0f;		//�o�i�i�̔�̊��鑬�x��������́B

BananaPeel::BananaPeel()
{
	m_model.Init(L"Assets/modelData/BananaPeel.cmo");

	//�S�[�X�g�I�u�W�F�N�g�̍쐬�B
	m_ghost.CreateBox(m_position, m_rotation, m_ghostObjectScale);
}


BananaPeel::~BananaPeel()
{
}

void BananaPeel::Update()
{
	m_deathTimer++;
	//�o�i�i�̔炪������B
	if (m_deathTimer == DEATH_TIME)
	{
		Delete();
	}

	//�S�[�X�g�I�u�W�F�N�g�̔���B
	g_physics.ContactTest(m_pl->GetcharaCon(), [&](const btCollisionObject& contactObject) {
		if (m_ghost.IsSelf(contactObject)) {
			Delete();
			m_pl->SetStateSliped();
		}
		});

	m_stopTimer++;
	//�o�i�i�̔炪�����Ă���B
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
