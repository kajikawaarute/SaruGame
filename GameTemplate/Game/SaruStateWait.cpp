#include "stdafx.h"
#include "SaruStateWait.h"
#include "Saru.h"
#include "Player.h"

const float SARU_PLAYER_DISTANCE = 600.0f;		//サルとプレイヤーの距離。
const float SARU_ANGLE = 50.0f;					//サルの視野。

void SaruStateWait::OnEnter()
{
}

void SaruStateWait::Update()
{
	CVector3 saruFoward = CVector3::AxisZ();
	m_saru->m_rotation.Multiply(saruFoward);
	//サルからプレイヤーに伸びるベクトルを求める。
	CVector3 toSaruDir = m_saru->m_pl->GetPos() - m_saru->m_position;
	float toSaruLen = toSaruDir.Length();
	toSaruDir.Normalize();

	float d = saruFoward.Dot(toSaruDir);

	float angle = acos(d);

	m_saru->Move();
	m_saru->m_moveSpeed = CVector3::Zero();

	//サルがプレイヤーを発見する範囲
	if (fabsf(angle) < CMath::DegToRad(SARU_ANGLE) && toSaruLen < SARU_PLAYER_DISTANCE)
	{
		m_saru->ChangeStateFound();
	}
	m_saru->AttackDistance();
}

void SaruStateWait::OnLeave()
{
}
