#include "stdafx.h"
#include "SaruStateStun.h"
#include "Saru.h"
#include "Player.h"

void SaruStateStun::OnEnter()
{
	m_saru->SaruStunSound();

	m_saru->m_playEffectHandle = g_effekseerManager->Play(m_saru->m_saruDamegeEffect, 
		m_saru->m_position.x, m_saru->m_position.y, m_saru->m_position.z);
}

void SaruStateStun::Update()
{
	m_saru->m_moveSpeed.x = 0.0f;
	m_saru->m_moveSpeed.z = 0.0f;

	//サルからプレイヤーに伸びるベクトルを求める。
	CVector3 toSaruDir = m_saru->m_pl->GetPos() - m_saru->m_position;
	//プレイヤーの方を見る
	m_saru->m_angle = atan2f(toSaruDir.x, toSaruDir.z);
	m_saru->m_rotation.SetRotation(CVector3::AxisY(), m_saru->m_angle);

	m_saru->ChangeStateWaitAnim();
}

void SaruStateStun::OnLeave()
{
}
