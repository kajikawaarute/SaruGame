#include "stdafx.h"
#include "GunEnemyStateAttack.h"
#include "GunEnemy.h"
#include "Player.h"
#include "IGameObjectManager.h"

const float GUNENEMY_WAIT_DISTANCE = 700.0f;	//待機状態になる距離。
const float GUNENEMY_FUTTOBI_DISTANCE = 120.0f;	//プレイヤーを吹き飛ばすまでの距離。
const float GUNENEMY_FUTTOBI_POWER = 2500.0f;	//ガンエネミーのプレイヤーを吹っ飛ばす力。


void GunEnemyStateAttack::OnEnter()
{
	
}

void GunEnemyStateAttack::Update()
{
	//ガンエネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toGunEnemyDir = m_gunEnemy->m_player->GetPos() - m_gunEnemy->m_position;
	float toGunEnemyLen = toGunEnemyDir.Length();
	//プレイヤーの方を見る
	float angle = 0.0f;
	angle = atan2f(toGunEnemyDir.x, toGunEnemyDir.z);
	m_gunEnemy->m_rotation.SetRotation(CVector3::AxisY(), angle);

	toGunEnemyDir.Normalize();
	m_gunEnemy->m_player->SetAttackedPower(toGunEnemyDir * GUNENEMY_FUTTOBI_POWER);

	//ガンエネミーの前方向を計算する。
	CVector3 gunEnemyFoward = CVector3::AxisZ();
	m_gunEnemy->m_rotation.Multiply(gunEnemyFoward);

	m_gunEnemy->Attack();

	//プレイヤーが近づいたら吹き飛ばす。
	if (toGunEnemyLen < GUNENEMY_FUTTOBI_DISTANCE) {
		m_gunEnemy->m_player->SetAttackedPower(toGunEnemyDir * GUNENEMY_FUTTOBI_POWER);
		m_gunEnemy->m_player->Attacked();
	}


	//待機状態になる範囲。
	if (toGunEnemyLen > GUNENEMY_WAIT_DISTANCE) {
		m_gunEnemy->m_enGunEnemyState = m_gunEnemy->enState_wait;
	}
}

void GunEnemyStateAttack::OnLeave()
{
}
