#include "stdafx.h"
#include "SaruStateRun.h"
#include "Saru.h"
#include "Player.h"

const float SARU_PLAYER_DISTANCE = 700.0f;		//�T���ƃv���C���[�̋����B

void SaruStateRun::OnEnter()
{
}

void SaruStateRun::Update()
{
	CVector3 saruFoward = CVector3::AxisZ();
	m_saru->m_rotation.Multiply(saruFoward);
	//�T������v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toSaruDir = m_saru->m_pl->GetPos() - m_saru->m_position;
	float toSaruLen = toSaruDir.Length();
	toSaruDir.Normalize();

	m_saru->m_moveSpeed -= toSaruDir;
	m_saru->Run();
	m_saru->BanaPeelThrow();
	
	if (toSaruLen > SARU_PLAYER_DISTANCE)
	{
		m_saru->ChangeStateWait();
	}
	m_saru->AttackDistance();

	m_saru->m_playEffectHandle = g_effekseerManager->Play(m_saru->m_saruRunEffect, m_saru->m_position.x,
															m_saru->m_position.y, m_saru->m_position.z);
}

void SaruStateRun::OnLeave()
{
}
