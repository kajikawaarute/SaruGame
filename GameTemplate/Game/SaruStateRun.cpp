#include "stdafx.h"
#include "SaruStateRun.h"
#include "Saru.h"
#include "Player.h"

void SaruStateRun::OnEnter()
{
}

void SaruStateRun::Update()
{
	CVector3 saruFoward = CVector3::AxisZ();
	m_saru->m_rotation.Multiply(saruFoward);
	//サルからプレイヤーに伸びるベクトルを求める。
	CVector3 toSaruDir = m_saru->m_pl->GetPos() - m_saru->m_position;
	float toSaruLen = toSaruDir.Length();

	m_saru->Run();
	m_saru->BanaPeelThrow();
	m_saru->m_moveSpeed = toSaruDir;
	if (toSaruLen > 700.0f)
	{
		m_saru->ChangeStateWait();
	}
	m_saru->AttackDistance();
}

void SaruStateRun::OnLeave()
{
}
