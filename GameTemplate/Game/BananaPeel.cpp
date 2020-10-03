#include "stdafx.h"
#include "BananaPeel.h"
#include "IGameObjectManager.h"
#include "Player.h"

const int DEATH_TIME = 60;		//�o�i�i�̔炪������^�C���B
const int STOP_TIME = 30;		//�o�i�i�̔炪�~�܂�^�C���B
const float BANANAPEEL_SPEED_POWER = 10.0f;		//�o�i�i�̔�̊��鑬�x��������́B

BananaPeel::BananaPeel()
{
	//���f���̏������B
	m_skinModel = g_goMgr.NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/BananaPeel.cmo");

	//�S�[�X�g�I�u�W�F�N�g�̍쐬�B
	m_ghost.CreateBox(m_position, m_rotation, m_ghostObjectScale);

	//�V���h�E���V�[�o�[��ݒ�B
	m_skinModel->SetShadowReciever();
}


BananaPeel::~BananaPeel()
{
	//�X�L�����f�����폜�B
	g_goMgr.DeleteGO(m_skinModel);
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

	//�S�[�X�g�I�u�W�F�N�g�̍��W��ݒ�B
	m_ghost.SetPosition(m_position);

	//�V���h�E�L���X�^�[��ݒ�B
	m_skinModel->SetShadowCaster();

	//�g�D�[�������_�[��ݒ�B
	m_skinModel->SetToonRender();

	//�X�L�����f���̍��W��ݒ�B
	m_skinModel->SetPosition(m_position);

	//�X�L�����f���̉�]��ݒ�B
	m_skinModel->SetRotation(m_rotation);
}

void BananaPeel::Delete()
{
	g_goMgr.DeleteGO(this);
	//�X�L�����f�����폜�B
	g_goMgr.DeleteGO(m_skinModel);
}
