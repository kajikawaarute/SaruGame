#include "stdafx.h"
#include "GunEnemyStateFound.h"
#include "GunEnemy.h"

const float GUNENEMY_POSITION_Y_UP = 7.5f;		//ガンエネミーが上に上がる座標。

void GunEnemyStateFound::OnEnter()
{
}

void GunEnemyStateFound::Update()
{
	m_gunEnemy->Found();
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
