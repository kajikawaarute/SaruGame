#include "stdafx.h"
#include "GunEnemyStateWait.h"
#include "GunEnemy.h"
#include "Player.h"

const float GUNENEMY_ATTACK_DISTANCE = 600.0f;		//ガンエネミーが攻撃をする範囲。

void GunEnemyStateWait::OnEnter()
{
}

void GunEnemyStateWait::Update()
{
	//ガンエネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toSaruDir = m_gunEnemy->m_player->GetPos() - m_gunEnemy->m_position;
	float toSaruLen = toSaruDir.Length();

	//プレイヤーを見つける範囲。
	if (toSaruLen < GUNENEMY_ATTACK_DISTANCE) {
		m_gunEnemy->ChangeStateFound();
	}
}

void GunEnemyStateWait::OnLeave()
{
}
