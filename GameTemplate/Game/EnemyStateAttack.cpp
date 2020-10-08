#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "EnemyStateAttack.h"

const int ENEMY_WAIT_TIME = 60;				//�G�l�~�[���ҋ@��ԂɂȂ�^�C���B
const float ENEMY_FUTTOBI_POWER = 2000.0f;	//�v���C���[�𐁂���΂��́B

void EnemyStateAttack::OnEnter()
{
	m_enemy->m_moveSpeed.x = 0.0f;
	m_enemy->m_moveSpeed.z = 0.0f;

	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toEnemyDir = m_enemy->m_pl->GetPos() - m_enemy->m_position;

	m_enemy->m_rotation.SetRotation(CVector3::AxisY(), atan2f(toEnemyDir.x, toEnemyDir.z));
	toEnemyDir.Normalize();

	m_enemy->m_pl->SetAttackedPower(toEnemyDir * ENEMY_FUTTOBI_POWER);
	m_enemy->m_pl->Attacked();
}

void EnemyStateAttack::Update()
{
	m_enemy->AddWaitTimer();
	if (m_enemy->GetWaitTimer() > ENEMY_WAIT_TIME) {
		m_enemy->ChangeStateWait();
		m_enemy->ReSetWaitTimer();
	}
}

void EnemyStateAttack::OnLeave()
{
}
