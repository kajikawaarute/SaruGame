#include "stdafx.h"
#include "PlayerStateSaruGet.h"
#include "Player.h"
#include "Saru.h"

void PlayerStateSaruGet::OnEnter()
{
}

void PlayerStateSaruGet::Update()
{
	CVector3 plFoward = CVector3::AxisZ();
	m_player->m_rotation.Multiply(plFoward);
	//サルからプレイヤーに伸びるベクトルを求める。
	for (int i = 0; i < m_player->m_sarus.size(); i++) {
		CVector3 toPlayerDir = m_player->m_sarus[i]->GetPos() - m_player->m_position;
		float toEnemyLen = toPlayerDir.Length();
		toPlayerDir.Normalize();

		float d = plFoward.Dot(toPlayerDir);
		float angle = acos(d);

		if (fabsf(angle) < CMath::DegToRad(45.0f) && toEnemyLen < 150.0f)
		{
			m_player->m_sarus[i]->GetSaru();
		}
	}
}

void PlayerStateSaruGet::OnLeave()
{
	m_player->ChangeStateWaitAnim();
}
