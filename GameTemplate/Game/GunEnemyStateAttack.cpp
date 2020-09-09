#include "stdafx.h"
#include "GunEnemyStateAttack.h"
#include "GunEnemy.h"
#include "Player.h"
#include "IGameObjectManager.h"

const float GUNENEMY_WAIT_DISTANCE = 700.0f;	//�ҋ@��ԂɂȂ鋗���B
const float GUNENEMY_FUTTOBI_DISTANCE = 120.0f;	//�v���C���[�𐁂���΂��܂ł̋����B
const float GUNENEMY_FUTTOBI_POWER = 2500.0f;	//�K���G�l�~�[�̃v���C���[�𐁂���΂��́B


void GunEnemyStateAttack::OnEnter()
{
	
}

void GunEnemyStateAttack::Update()
{
	//�K���G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toGunEnemyDir = m_gunEnemy->m_player->GetPos() - m_gunEnemy->m_position;
	float toGunEnemyLen = toGunEnemyDir.Length();
	//�v���C���[�̕�������
	float angle = 0.0f;
	angle = atan2f(toGunEnemyDir.x, toGunEnemyDir.z);
	m_gunEnemy->m_rotation.SetRotation(CVector3::AxisY(), angle);

	toGunEnemyDir.Normalize();
	m_gunEnemy->m_player->SetAttackedPower(toGunEnemyDir * GUNENEMY_FUTTOBI_POWER);

	//�K���G�l�~�[�̑O�������v�Z����B
	CVector3 gunEnemyFoward = CVector3::AxisZ();
	m_gunEnemy->m_rotation.Multiply(gunEnemyFoward);

	m_gunEnemy->Attack();

	//�v���C���[���߂Â����琁����΂��B
	if (toGunEnemyLen < GUNENEMY_FUTTOBI_DISTANCE) {
		m_gunEnemy->m_player->SetAttackedPower(toGunEnemyDir * GUNENEMY_FUTTOBI_POWER);
		m_gunEnemy->m_player->Attacked();
	}


	//�ҋ@��ԂɂȂ�͈́B
	if (toGunEnemyLen > GUNENEMY_WAIT_DISTANCE) {
		m_gunEnemy->m_enGunEnemyState = m_gunEnemy->enState_wait;
	}
}

void GunEnemyStateAttack::OnLeave()
{
}
