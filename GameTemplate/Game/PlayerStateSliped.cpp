#include "stdafx.h"
#include "PlayerStateSliped.h"
#include "Player.h"

void PlayerStateSliped::OnEnter()
{
}

void PlayerStateSliped::Update()
{
	m_player->m_moveSpeed.x = 0.0f;
	m_player->m_moveSpeed.z = 0.0f;

	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), 5.0f);
	m_player->m_rotation.Multiply(addRot);
}

void PlayerStateSliped::OnLeave()
{
	m_player->ChangeStateWaitAnim();
}
