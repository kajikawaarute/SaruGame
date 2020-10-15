#include "stdafx.h"
#include "GunEnemyBullet.h"
#include "Player.h"

const float GUN_SPPED_POWER = 30.0f;		//�e�̑��x�𑬂�����́B
const int DEATH_TIME = 20;					//�e��������^�C���B

GunEnemyBullet::GunEnemyBullet()
{
	//���f���̏������B
	m_skinModel = NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/GunEnemyBullet.cmo");

	//�S�[�X�g�I�u�W�F�N�g���쐬�B
	m_ghostObject.CreateBox(m_position, m_rotation, m_ghostObjectScale);

	//�V���h�E���V�[�o�[��ݒ�B
	m_skinModel->SetShadowReciever();
}


GunEnemyBullet::~GunEnemyBullet()
{
	//�X�L�����f�����폜�B
	DeleteGO(m_skinModel);
}

void GunEnemyBullet::Update()
{
	//�e����ݒ�B
	m_position += m_moveSpeed * GUN_SPPED_POWER;

	//�S�[�X�g�I�u�W�F�N�g�̔���B
	ContactTestPhysicsWorld(m_pl->GetcharaCon(), [&](const btCollisionObject& contactObject) {
		if (m_ghostObject.IsSelf(contactObject)) {
			Delete();
			m_pl->Attacked();
		}
		});

	m_deathTimer++;
	//�e��������B
	if (m_deathTimer == DEATH_TIME)
	{
		Delete();
	}

	//�S�[�X�g�I�u�W�F�N�g�̍��W��ݒ�B
	m_ghostObject.SetPosition(m_position);

	//�V���h�E�L���X�^�[��ݒ�B
	m_skinModel->SetShadowCaster();

	//�g�D�[�������_�[��ݒ�B
	m_skinModel->SetToonRender();

	//�X�L�����f���̍��W��ݒ�B
	m_skinModel->SetPosition(m_position);

	//�X�L�����f���̉�]��ݒ�B
	m_skinModel->SetRotation(m_rotation);
}


void GunEnemyBullet::Delete()
{
	DeleteGO(this);
	//�X�L�����f�����폜�B
	DeleteGO(m_skinModel);
}
