#include "stdafx.h"
#include "GunEnemy.h"
#include "Player.h"
#include "GunEnemyBullet.h"

const int GUNENEMY_BULLET_TIME = 30;			//ガンエネミーが弾丸を発射するタイム。
const float GUNENEMY_BULLET_POSITION_Y = 120.0f;	//ガンエネミーの弾丸を発射するY座標。
const float GUNENEMY_DEATH_SE_VOLUME = 1.5f;				//ガンエネミ－が倒された時のSEのボリューム

GunEnemy::GunEnemy()
{
	//モデルの初期化。
	m_skinModel = NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/GunEnemy.cmo");

	//アニメーションをロード。
	m_animClip[enAnim_wait].Load(L"Assets/animData/GunEnemy-wait.tka");
	m_animClip[enAnim_attack].Load(L"Assets/animData/GunEnemy-attack.tka");
	m_animClip[enAnim_found].Load(L"Assets/animData/GunEnemy-found.tka");

	//アニメーションのループフラグを設定。
	m_animClip[enAnim_wait].SetLoopFlag(true);
	m_animClip[enAnim_attack].SetLoopFlag(true);

	//アニメーションの初期化
	m_animation.Init(m_skinModel->GetSkinModel(), m_animClip, enAnim_num);

	//ガンエネミーの初期アニメーション
	m_enAnimClip = enAnim_wait;

	//エフェクトの生成。
	m_gunEnemyDeathEffekt = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/EnemyDeath.efk");
	m_gunEnemySandDustEffekt = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/GunEnemySandDust.efk");	

	//状態を初期化する。
	m_gunEnemyStateWait.Init(this);
	m_gunEnemyStateAttack.Init(this);
	m_gunEnemyStateFound.Init(this);

	//ガンエネミーの初期状態
	m_currentState = &m_gunEnemyStateWait;
}

GunEnemy::~GunEnemy()
{
	DeleteGO(m_gunBullet);
	//スキンモデルを削除。
	DeleteGO(m_skinModel);
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
	//アニメーションの更新。
	m_animation.Update(GameTime().GetFrameDeltaTime());

	//シャドウキャスターを設定。
	m_skinModel->SetShadowCaster();

	//トゥーンレンダーを設定。
	m_skinModel->SetToonRender();

	//スキンモデルの座標を設定。
	m_skinModel->SetPosition(m_position);

	//スキンモデルの回転を設定。
	m_skinModel->SetRotation(m_rotation);
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
		//サウンドの再生。
		prefab::CSoundSource* gunEnemySE_Shot = NewGO<prefab::CSoundSource>();
		gunEnemySE_Shot->Init(L"Assets/Sound/GunEnemy_shot.wav");
		gunEnemySE_Shot->Play(false);

		//弾丸の生成。
		m_gunBullet = NewGO<GunEnemyBullet>();
		m_gunBullet->SetPlayer(m_player);
		m_gunBullet->SetMoveSpd(gunEnemyFoward);
		m_gunBullet->SetPosition(positionY);
		m_bulletTimer = 0;
	}
}

void GunEnemy::Death()
{
	//エフェクトを表示。
	m_playEffectHandle = g_effekseerManager->Play(m_gunEnemyDeathEffekt, m_position.x, m_position.y, m_position.z);

	//サウンドの再生。
	prefab::CSoundSource* gunEnemySE_death = NewGO<prefab::CSoundSource>();
	gunEnemySE_death->Init(L"Assets/Sound/EnemySE_Death.wav");
	gunEnemySE_death->Play(false);
	gunEnemySE_death->SetVolume(GUNENEMY_DEATH_SE_VOLUME);

	DeleteGO(this);
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
