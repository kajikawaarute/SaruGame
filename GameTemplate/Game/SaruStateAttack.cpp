#include "stdafx.h"
#include "SaruStateAttack.h"
#include "Saru.h"
#include "Player.h"

const float SARU_FUTTOBI_POWER = 2700.0f;		//�T���̃v���C���[�𐁂���΂��́B

void SaruStateAttack::OnEnter()
{
	//�T������v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toSaruDir = m_saru->m_pl->GetPos() - m_saru->m_position;
	//�v���C���[�̕�������
	m_saru->m_angle = atan2f(toSaruDir.x, toSaruDir.z);
	m_saru->m_rotation.SetRotation(CVector3::AxisY(), m_saru->m_angle);

	toSaruDir.Normalize();
	m_saru->m_pl->SetAttackedPower(toSaruDir * SARU_FUTTOBI_POWER);
	m_saru->m_pl->Attacked();

	m_saru->SaruAttackSound();
}

void SaruStateAttack::Update()
{
	m_saru->ChangeStateWaitAnim();
}

void SaruStateAttack::OnLeave()
{
}
