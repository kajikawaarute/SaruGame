#include "stdafx.h"
#include "PlayerStateAttack.h"
#include "Player.h"
#include "Enemy.h"
#include "Saru.h"

void PlayerStateAttack::OnEnter()
{
}

void PlayerStateAttack::Update()
{
	m_player->m_moveSpeed.x = 0.0f;
	m_player->m_moveSpeed.z = 0.0f;

	CVector3 plFoward = CVector3::AxisZ();
	m_player->m_rotation.Multiply(plFoward);
	//エネミーを倒す
	for (int i = 0; i < m_player->m_enemys.size(); i++) {
		CVector3 toPlayer_EnemyDir = m_player->m_enemys[i]->GetPos() - m_player->m_position;
		float toEnemyLen = toPlayer_EnemyDir.Length();
		toPlayer_EnemyDir.Normalize();

		float d = plFoward.Dot(toPlayer_EnemyDir);
		float angle = acos(d);

		if (fabsf(angle) < CMath::DegToRad(45.0f) && toEnemyLen < 150.0f)
		{
			m_player->m_enemys[i]->Delete();
		}
	}

	//サルをひるませる
	for (int i = 0; i < m_player->m_sarus.size(); i++) {
		CVector3 toPlayer_SaruDir = m_player->m_sarus[i]->GetPos() - m_player->m_position;
		float toSaruLen = toPlayer_SaruDir.Length();
		toPlayer_SaruDir.Normalize();

		float d = plFoward.Dot(toPlayer_SaruDir);
		float angle = acos(d);

		if (fabsf(angle) < CMath::DegToRad(45.0f) && toSaruLen < 150.0f)
		{
			m_player->m_sarus[i]->Stun();
		}
	}
}

void PlayerStateAttack::OnLeave()
{
	m_player->ChangeStateWaitAnim();
}
