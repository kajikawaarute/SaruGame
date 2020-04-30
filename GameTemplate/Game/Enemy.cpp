#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "IGameObjectManager.h"

Enemy::Enemy()
{
	m_model.Init(L"Assets/modelData/Enemy.cmo");

	//アニメーションのロード
	m_animationClip[enAnim_walk].Load(L"Assets/animData/Enemy-walk.tka");
	m_animationClip[enAnim_taiki].Load(L"Assets/animData/Enemy-taiki.tka");

	//アニメーションのループを設定
	m_animationClip[enAnim_walk].SetLoopFlag(true);
	m_animationClip[enAnim_taiki].SetLoopFlag(true);

	//アニメーションを初期化
	m_animation.Init(m_model, m_animationClip, enAnim_num);

	//エネミーの初期状態
	m_enEnemyState = enState_taiki;

	//エネミーの初期アニメーション
	m_enAnimClip = enAnim_taiki;
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	CVector3 enemyFoward = CVector3::AxisZ();
	m_rotation.Multiply(enemyFoward);
	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toEnemyDir = m_pl->GetPos() - m_position;
	float toEnemyLen = toEnemyDir.Length();
	toEnemyDir.Normalize();

	float d = enemyFoward.Dot(toEnemyDir);
	float angle = acos(d);

	//エネミーの状態
	switch (m_enEnemyState)
	{
	case Enemy::enState_taiki:		//待機状態
		m_enAnimClip = enAnim_taiki;
		AttackDistance();
		m_moveSpeed = CVector3::Zero();
		if (fabsf(angle) < CMath::DegToRad(90.0f) && toEnemyLen < 700.0f) {
			m_enEnemyState = enState_move;
		}
		break;
	case Enemy::enState_move:		//移動状態
		m_enAnimClip = enAnim_walk;
		Move();
		AttackDistance();
		m_moveSpeed = toEnemyDir;
		if (toEnemyLen > 700.0f) {
			m_enEnemyState = enState_taiki;
		}
		break;
	case Enemy::enState_attack:		//攻撃状態
		Attack();
		m_taikiTimer++;
		if (m_taikiTimer == 60) {
			m_enEnemyState = enState_taiki;
			m_taikiTimer = 0;
		}
		break;
	}

	//エネミーのアニメーション
	switch (m_enAnimClip)
	{
	case enAnim_taiki:
		m_animation.Play(enAnim_taiki, m_animTime);
		break;
	case enAnim_walk:
		m_animation.Play(enAnim_walk, m_animTime);
		break;
	}

	m_animation.Update(1.0f / 30.0f);

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Enemy::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Enemy::Move()
{
	m_moveSpeed.Normalize();
	m_moveSpeed.x *= 5.0f;
	m_moveSpeed.z *= 5.0f;
	m_moveSpeed.y = 0.0f;
	m_position += m_moveSpeed;

	Turn();
}


void Enemy::Turn()
{
	CVector3 toEnemyDir = m_pl->GetPos() - m_position;
	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toEnemyDir.x, toEnemyDir.z));

}

void Enemy::Attack()
{
	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toEnemyDir = m_pl->GetPos() - m_position;

	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toEnemyDir.x, toEnemyDir.z));
	m_pl->GetMoveSpd() = toEnemyDir * 2.0f;
	m_pl->Attacked();
}

void Enemy::AttackDistance()
{
	CVector3 enemyFoward = CVector3::AxisZ();
	m_rotation.Multiply(enemyFoward);
	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toEnemyDir = m_pl->GetPos() - m_position;
	float toEnemyLen = toEnemyDir.Length();
	toEnemyDir.Normalize();

	float d = enemyFoward.Dot(toEnemyDir);
	float angle = acos(d);

	if (toEnemyLen < 90.0f) {
		m_enEnemyState = enState_attack;
	}
}

void Enemy::Delete()
{
	g_goMgr.DeleteGO(this);
	m_pl->DeleteEnemy(this);
}
