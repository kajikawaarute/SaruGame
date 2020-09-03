#include "stdafx.h"
#include "GunEnemy.h"
#include "IGameObjectManager.h"
#include "Player.h"
#include "GunEnemyBullet.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"


const float GUNENEMY_ATTACK_DISTANCE = 600.0f;		//ガンエネミーが攻撃をする範囲。
const int GUNENEMY_BULLET_TIME = 30;			//ガンエネミーが弾丸を発射するタイム。
const float GUNENEMY_BULLET_POSITION_Y = 120.0f;	//ガンエネミーの弾丸を発射するY座標。

GunEnemy::GunEnemy()
{
	m_model.Init(L"Assets/modelData/GunEnemy.cmo");

	//アニメーションをロード。
	m_animClip[enAnim_wait].Load(L"Assets/animData/GunEnemy-wait.tka");
	m_animClip[enAnim_attack].Load(L"Assets/animData/GunEnemy-attack.tka");
	m_animClip[enAnim_found].Load(L"Assets/animData/GunEnemy-found.tka");

	//エフェクトの生成。
	m_gunEnemyDeathEffekt = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/EnemyDeath.efk");

	//アニメーションのループフラグを設定。
	m_animClip[enAnim_wait].SetLoopFlag(true);
	m_animClip[enAnim_attack].SetLoopFlag(true);

	//状態を初期化する。
	m_gunEnemyStateWait.Init(this);
	m_gunEnemyStateAttack.Init(this);
	m_gunEnemyStateFound.Init(this);

	//アニメーションの初期化
	m_animation.Init(m_model, m_animClip, enAnim_num);

	//ガンエネミーの初期アニメーション
	m_enAnimClip = enAnim_wait;

	//ガンエネミーの初期状態
	m_currentState = &m_gunEnemyStateWait;

	//シャドウレシーバーを設定。
	m_model.SetShadowReciever(true);
}

GunEnemy::~GunEnemy()
{
}

void GunEnemy::Update()
{
	//ガンエネミーの状態
	m_currentState->Update();
	ChangeState(m_enGunEnemyState);

	switch (m_enAnimClip)
	{
	case GunEnemy::enAnim_wait:		//待機アニメーション
		m_animation.Play(enAnim_wait, m_animTime);
		break;
	case GunEnemy::enAnim_attack:	//攻撃アニメーション
		m_animation.Play(enAnim_attack, m_animTime);
		break;
	case GunEnemy::enAnim_found:	//見つかった時のアニメーション
		m_animation.Play(enAnim_found, m_animTime);
		break;
	}
	m_animation.Update(GameTime().GetFrameDeltaTime());

	//シャドウキャスターを設定。
	ShadowMap::GetInstance().RegistShadowCaster(&m_model);

	//トゥーンレンダーを設定。
	ToonRender::GetInstance().RegistToonRender(&m_model);

	//ワールド行列の更新
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void GunEnemy::Draw()
{
	m_model.Draw(
		enRenderMode_Normal, 
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

void GunEnemy::Attack()
{
	CVector3 positionY = m_position;
	positionY.y = m_position.y + GUNENEMY_BULLET_POSITION_Y;

	//ガンエネミーの前方向を計算する。
	CVector3 gunEnemyFoward = CVector3::AxisZ();
	m_rotation.Multiply(gunEnemyFoward);

	m_bulletTimer++;
	if (m_bulletTimer == GUNENEMY_BULLET_TIME) {
		GunEnemyBullet* gunBullet = g_goMgr.NewGO<GunEnemyBullet>();
		gunBullet->SetPlayer(m_player);
		gunBullet->SetMoveSpd(gunEnemyFoward);
		gunBullet->SetPosition(positionY);
		m_bulletTimer = 0;
	}
}

void GunEnemy::AttackDistance()
{
	//ガンエネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toSaruDir = m_player->GetPos() - m_position;
	float toSaruLen = toSaruDir.Length();

	//プレイヤーを見つける範囲。
	if (toSaruLen < GUNENEMY_ATTACK_DISTANCE) {
		m_enGunEnemyState = enState_found;
	}
}

void GunEnemy::Death()
{
	//エフェクトを表示。
	m_playEffectHandle = g_effekseerManager->Play(m_gunEnemyDeathEffekt, m_position.x, m_position.y, m_position.z);

	g_goMgr.DeleteGO(this);
	m_player->DeleteGunEnemy(this);
}

void GunEnemy::ChangeState(EnGunEnemyState nextState)
{
	IGunEnemyState* pNextState = nullptr;
	EnAnimationClip nextAnimClip = enAnim_wait;
	switch (nextState)
	{
	case GunEnemy::enState_wait:
		//現在の状態を待機状態にする。
		pNextState = &m_gunEnemyStateWait;
		nextAnimClip = enAnim_wait;
		break;
	case GunEnemy::enState_attack:
		//現在の状態を攻撃状態にする。
		pNextState = &m_gunEnemyStateAttack;
		nextAnimClip = enAnim_attack;
		break;
	case GunEnemy::enState_found:
		//現在の状態を見つかった状態にする。
		pNextState = &m_gunEnemyStateFound;
		nextAnimClip = enAnim_found;
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
