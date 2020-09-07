#include "stdafx.h"
#include "PlayerStateAttack.h"
#include "Player.h"
#include "Enemy.h"
#include "GunEnemy.h"
#include "Saru.h"

const float PLAYER_ATTACK_DISTANCE = 170.0f;	//プレイヤーの攻撃距離。
const float PLAYER_ATTACK_ANGLE = 45.0f;		//プレイヤーの攻撃視野。

void PlayerStateAttack::OnEnter()
{
}

void PlayerStateAttack::Update()
{
	CVector3 plFoward = CVector3::AxisZ();
	m_player->m_rotation.Multiply(plFoward);
	//エネミーを倒す
	for (int i = 0; i < m_player->m_enemys.size(); i++) {
		CVector3 toPlayer_EnemyDir = m_player->m_enemys[i]->GetPos() - m_player->m_position;
		float toEnemyLen = toPlayer_EnemyDir.Length();
		toPlayer_EnemyDir.Normalize();

		float d = plFoward.Dot(toPlayer_EnemyDir);
		float angle = acos(d);

		if (fabsf(angle) < CMath::DegToRad(PLAYER_ATTACK_ANGLE) && toEnemyLen < PLAYER_ATTACK_DISTANCE)
		{
			m_player->m_enemys[i]->Delete();
		}
	}

	//ガンエネミーを倒す。
	for (int i = 0; i < m_player->m_gunEnemys.size(); i++) {
		CVector3 toPlayer_GunEnemyDir = m_player->m_gunEnemys[i]->GetPosition() - m_player->m_position;
		float toGunEnemyLen = toPlayer_GunEnemyDir.Length();
		toPlayer_GunEnemyDir.Normalize();

		float d = plFoward.Dot(toPlayer_GunEnemyDir);
		float angle = acos(d);

		if (fabsf(angle) < CMath::DegToRad(PLAYER_ATTACK_ANGLE) && toGunEnemyLen < PLAYER_ATTACK_DISTANCE)
		{
			m_player->m_gunEnemys[i]->Death();
		}
	}

	//サルをひるませる
	for (int i = 0; i < m_player->m_sarus.size(); i++) {
		CVector3 toPlayer_SaruDir = m_player->m_sarus[i]->GetPos() - m_player->m_position;
		float toSaruLen = toPlayer_SaruDir.Length();
		toPlayer_SaruDir.Normalize();

		float d = plFoward.Dot(toPlayer_SaruDir);
		float angle = acos(d);

		if (fabsf(angle) < CMath::DegToRad(PLAYER_ATTACK_ANGLE) && toSaruLen < PLAYER_ATTACK_DISTANCE)
		{
			m_player->m_sarus[i]->Stun();
		}
	}

	m_player->ChangeStateWaitAnim();
}

void PlayerStateAttack::OnLeave()
{
	
}
