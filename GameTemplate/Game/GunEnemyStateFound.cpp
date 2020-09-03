#include "stdafx.h"
#include "GunEnemyStateFound.h"
#include "GunEnemy.h"
#include "Player.h"

const float GUNENEMY_POSITION_Y_UP = 7.5f;		//ガンエネミーが上に上がる座標。

void GunEnemyStateFound::OnEnter()
{
}

void GunEnemyStateFound::Update()
{
	//ガンエネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toSaruDir = m_gunEnemy->m_player->GetPos() - m_gunEnemy->m_position;
	//プレイヤーの方を見る
	float angle = 0.0f;
	angle = atan2f(toSaruDir.x, toSaruDir.z);
	m_gunEnemy->m_rotation.SetRotation(CVector3::AxisY(), angle);

	if (m_gunEnemy->m_foundFlag == false) {
		m_gunEnemy->m_position.y += GUNENEMY_POSITION_Y_UP;
	}
	if (m_gunEnemy->m_animation.IsPlaying() != true) {
		m_gunEnemy->m_enGunEnemyState = m_gunEnemy->enState_attack;
		m_gunEnemy->m_foundFlag = true;
	}
}

void GunEnemyStateFound::OnLeave()
{
}
