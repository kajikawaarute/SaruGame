#include "stdafx.h"
#include "GunEnemyStateWait.h"
#include "GunEnemy.h"
#include "Player.h"

const float GUNENEMY_ATTACK_DISTANCE = 600.0f;		//�K���G�l�~�[���U��������͈́B

void GunEnemyStateWait::OnEnter()
{
}

void GunEnemyStateWait::Update()
{
	//�K���G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toSaruDir = m_gunEnemy->m_player->GetPos() - m_gunEnemy->m_position;
	float toSaruLen = toSaruDir.Length();

	//�v���C���[��������͈́B
	if (toSaruLen < GUNENEMY_ATTACK_DISTANCE) {
		m_gunEnemy->ChangeStateFound();
	}
}

void GunEnemyStateWait::OnLeave()
{
}
