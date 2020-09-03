#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"

const float ENEMY_MOVE_SPPED = 5.0f;		//エネミーの移動速度。
const float ENEMY_FUTTOBI_POWER = 1200.0f;	//プレイヤーを吹っ飛ばす力。
const float ENEMY_FOUND_PLAYER_DISTANCE = 90.0f;		//エネミーがプレイヤーを見つける距離。

Enemy::Enemy()
{
	//モデルの初期化。
	m_model.Init(L"Assets/modelData/Enemy.cmo");

	//アニメーションのロード。
	m_animationClip[enAnim_walk].Load(L"Assets/animData/Enemy-walk.tka");
	m_animationClip[enAnim_wait].Load(L"Assets/animData/Enemy-taiki.tka");

	//エフェクトの生成。
	m_enemyDeathEffekt = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/EnemyDeath.efk");

	//アニメーションのループを設定。
	m_animationClip[enAnim_walk].SetLoopFlag(true);
	m_animationClip[enAnim_wait].SetLoopFlag(true);

	//アニメーションを初期化。
	m_animation.Init(m_model, m_animationClip, enAnim_num);

	//状態を初期化する。
	m_enemyStateAttack.Init(this);
	m_enemyStateWait.Init(this);
	m_enemyStateMove.Init(this);

	//エネミーの初期状態。
	m_currentState = &m_enemyStateWait;

	//エネミーの初期アニメーション。
	m_enAnimClip = enAnim_wait;

	//シャドウレシーバーを設定。
	m_model.SetShadowReciever(true);
}


Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//エネミーの状態
	m_currentState->Update();
	ChangeState(m_enEnemyState);

	//エネミーのアニメーション
	switch (m_enAnimClip)
	{
	case enAnim_wait:	//待機アニメーション。
		m_animation.Play(enAnim_wait, m_animTime);
		break;
	case enAnim_walk:	//歩きアニメーション
		m_animation.Play(enAnim_walk, m_animTime);
		break;
	}

	m_animation.Update(1.0f / 30.0f);

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//シャドウキャスターを設定。
	ShadowMap::GetInstance().RegistShadowCaster(&m_model);

	//トゥーンレンダを設定。
	ToonRender::GetInstance().RegistToonRender(&m_model);
}

void Enemy::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Enemy::Move()
{
	m_moveSpeed.Normalize();
	m_moveSpeed.x *= ENEMY_MOVE_SPPED;
	m_moveSpeed.z *= ENEMY_MOVE_SPPED;
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
	toEnemyDir.Normalize();

	m_pl->SetAttackedPower( toEnemyDir * ENEMY_FUTTOBI_POWER );
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

	//プレイヤーを見つける。
	if (toEnemyLen < ENEMY_FOUND_PLAYER_DISTANCE) {
		m_enEnemyState = enState_attack;
	}
}

void Enemy::Delete()
{
	//エフェクトを表示。
	m_playEffectHandle = g_effekseerManager->Play(m_enemyDeathEffekt, m_position.x, m_position.y, m_position.z);

	g_goMgr.DeleteGO(this);
	m_pl->DeleteEnemy(this);
}

void Enemy::ChangeState(EnEnemyState nextState)
{
	IEnenyState* pNextState = nullptr;
	EnAnimationClip nextAnimClip = enAnim_wait;
	switch (nextState)
	{
	case enState_wait:
		//現在の状態を待機状態にする。
		pNextState = &m_enemyStateWait;
		nextAnimClip = enAnim_wait;
		break;
	case enState_move:
		//現在の状態を移動状態にする。
		pNextState = &m_enemyStateMove;
		nextAnimClip = enAnim_walk;
		break;
	case enState_attack:
		//現在の状態を攻撃状態にする。
		pNextState = &m_enemyStateAttack;
		break;
	}
	if (pNextState != nullptr && pNextState != m_currentState) {
		//現在の状態と違う。
		if (m_currentState != nullptr) {
			//終了処理
			m_currentState->OnLeave();
		}
		m_currentState = pNextState;
		m_enAnimClip = nextAnimClip;
		//開始処理
		m_currentState->OnEnter();
	}
	
}
