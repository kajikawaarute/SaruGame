#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

const float ENEMY_GRAVITY = 5000.0f;					//エネミーにかかる重力(単位cm/秒)。
const float ENEMY_MOVE_SPPED = 400.0f;					//エネミーの移動速度。
const float ENEMY_FOUND_PLAYER_DISTANCE = 90.0f;		//エネミーがプレイヤーを見つける距離。
const float ENEMY_DEATH_SE_VOLUME = 1.5f;				//エネミ－が倒された時のSEのボリューム

Enemy::Enemy()
{
	//モデルの初期化。
	m_skinModel = NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/Enemy.cmo");

	//アニメーションのロード。
	m_animationClip[enAnim_walk].Load(L"Assets/animData/Enemy-walk.tka");
	m_animationClip[enAnim_wait].Load(L"Assets/animData/Enemy-taiki.tka");

	//アニメーションのループを設定。
	m_animationClip[enAnim_walk].SetLoopFlag(true);
	m_animationClip[enAnim_wait].SetLoopFlag(true);

	//アニメーションを初期化。
	m_animation.Init(m_skinModel->GetSkinModel(), m_animationClip, enAnim_num);

	//エネミーの初期アニメーション。
	m_enAnimClip = enAnim_wait;

	//シャドウレシーバーを設定。
	m_skinModel->SetShadowReciever();

	//エフェクトの生成。
	m_enemyDeathEffekt = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/EnemyDeath.efk");

	//状態を初期化する。
	m_enemyStateAttack.Init(this);
	m_enemyStateWait.Init(this);
	m_enemyStateMove.Init(this);

	//エネミーの初期状態。
	m_currentState = &m_enemyStateWait;
}


Enemy::~Enemy()
{
	//スキンモデルを削除。
	DeleteGO(m_skinModel);
}

bool Enemy::Start()
{
	//キャラクターコントローラーの初期化。
	m_charaCon.Init(30.0f, 30.0f, m_position);

	return true;
}

void Enemy::Update()
{
	m_moveSpeed.y -= ENEMY_GRAVITY * GameTime().GetFrameDeltaTime();

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

	//アニメーションの更新。
	m_animation.Update(GameTime().GetFrameDeltaTime());

	//シャドウキャスターを設定。
	m_skinModel->SetShadowCaster();

	//トゥーンレンダを設定。
	m_skinModel->SetToonRender();

	//キャラクターコントローラーの更新。
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);

	//スキンモデルの座標を設定。
	m_skinModel->SetPosition(m_position);

	//スキンモデルの回転を設定。
	m_skinModel->SetRotation(m_rotation);
}

void Enemy::Move()
{
	m_moveSpeed.Normalize();
	m_moveSpeed.x *= ENEMY_MOVE_SPPED;
	m_moveSpeed.z *= ENEMY_MOVE_SPPED;

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

	//サウンドの再生。
	prefab::CSoundSource* enemySE_Death = NewGO<prefab::CSoundSource>();
	enemySE_Death->Init(L"Assets/Sound/EnemySE_Death.wav");
	enemySE_Death->Play(false);
	enemySE_Death->SetVolume(ENEMY_DEATH_SE_VOLUME);

	DeleteGO(this);
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
