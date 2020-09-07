#include "stdafx.h"
#include "GunEnemyStateFound.h"
#include "GunEnemy.h"
#include "Player.h"

const float GUNENEMY_POSITION_Y_UP = 7.5f;		//ガンエネミーが上に上がる座標。

void GunEnemyStateFound::OnEnter()
{
	if (m_gunEnemy->m_sandDustFlag == false) {
		//エフェクトの表示。
		m_gunEnemy->m_playEffectHandle = g_effekseerManager->Play(
			m_gunEnemy->m_gunEnemySandDustEffekt,
			m_gunEnemy->m_position.x,
			m_gunEnemy->m_position.y,
			m_gunEnemy->m_position.z);
		m_gunEnemy->m_sandDustFlag = true;
	}
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
