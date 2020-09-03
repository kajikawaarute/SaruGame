#include "stdafx.h"
#include "PlayerStateSaruGet.h"
#include "Player.h"
#include "Saru.h"

const float PLAYER_SARU_DISTANCE = 150.0f;	//プレイヤーとサルの距離。
const float PLAYER_ANGLE = 45.0f;			//プレイヤーの視野。

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

		if (fabsf(angle) < CMath::DegToRad(PLAYER_ANGLE) && toEnemyLen < PLAYER_SARU_DISTANCE)
		{
			m_player->m_sarus[i]->GetSaru();
		}
	}
	m_player->ChangeStateWaitAnim();
}

void PlayerStateSaruGet::OnLeave()
{
}
