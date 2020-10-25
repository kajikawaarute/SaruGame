#include "stdafx.h"
#include "Saru.h"
#include "Player.h"
#include "BananaPeel.h"
#include "BikkuriMark.h"

const float SARU_GRAVITY = 2000.0f;				//サルにかかる重力(単位cm/秒)。
const float SARU_MOVE_SPPED = 300.0f;			//サルの移動速度。
const float SARU_RUN_SPPED = 1500.0f;			//サルの走っている時の移動速度。
const float SARU_ATTACK_DISTANCE = 90.0f;		//サルが攻撃する距離。
const int SARU_BANANAPEEL_TIME = 90;			//サルがバナナの皮を投げるタイム。
const float SARU_BIKKURIMARK_POSITION_Y = 160.0f;	//ビックリマークを表示する座標Yを設定。
const float SARU_PATH_DISTANCE = 50.0f;				//パスまでの距離。
const float SARU_STUN_SE_VOLUME = 1.5f;				//サルが怯んだ時のSEのボリューム

Saru::Saru()
{
	//モデルの初期化。
	m_skinModel = NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/Saru.cmo");

	//アニメーションを生成。
	m_animClip[enAnim_wait].Load(L"Assets/animData/Saru-taiki.tka");
	m_animClip[enAnim_run].Load(L"Assets/animData/Saru-run.tka");
	m_animClip[enAnim_attack].Load(L"Assets/animData/Saru-Attack.tka");
	m_animClip[enAnim_Get].Load(L"Assets/animData/Saru-Get.tka");
	m_animClip[enAnim_found].Load(L"Assets/animData/Saru-found.tka");

	//エフェクトをロード
	m_saruGetEffekt = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/SaruGet.efk");
	m_saruRunEffect = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/SaruRun.efk");
	m_saruDamegeEffect = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/SaruDamege.efk");

	//アニメーションのループを設定
	m_animClip[enAnim_wait].SetLoopFlag(true);
	m_animClip[enAnim_run].SetLoopFlag(true);

	//サルの初期アニメーション
	m_enAnimClip = enAnim_wait;

	//サルの初期状態
	m_currentState = &m_saruStateWait;
	m_enSaruState = enState_wait;

	//アニメーションの初期化
	m_animation.Init(m_skinModel->GetSkinModel(), m_animClip, enAnim_num);

	//状態を初期化する。
	m_saruStateWait.Init(this);
	m_saruStateRun.Init(this);
	m_saruStateAttack.Init(this);
	m_saruStateGet.Init(this);
	m_saruStateStun.Init(this);
	m_saruStateFound.Init(this);

	//シャドウレシーバーを設定
	m_skinModel->SetShadowReciever();
}

Saru::~Saru()
{
	DeleteGO(m_bikkuriMark);
	DeleteGO(m_banaPeel);
	//スキンモデルを削除。
	DeleteGO(m_skinModel);
}

bool Saru::Start()
{
	//キャラクターコントローラーの初期化。
	m_charaCon.Init(30.0f, 100.0f, m_position);

	return true;
}

void Saru::Update()
{
	m_moveSpeed.y -= SARU_GRAVITY * GameTime().GetFrameDeltaTime();

	//サルの状態
	m_currentState->Update();
	ChangeState(m_enSaruState);

	//パス移動
	if (m_pathList.size() > 0)
	{
		if (m_enSaruState == enState_wait) {
			auto diff = m_position - m_pathList[pathNum];
			if (diff.Length() < SARU_PATH_DISTANCE)
			{
				if (pathNum < m_pathList.size() - 1)
				{
					pathNum++;
				}
				else pathNum = 0;
			}
			auto addSpeed = diff;
			m_moveSpeed.y -= addSpeed.y;
			addSpeed.Normalize();
			m_angle = atan2f(-addSpeed.x, -addSpeed.z);
			m_rotation.SetRotation(CVector3::AxisY(), m_angle);
			m_moveSpeed.x -= addSpeed.x * SARU_MOVE_SPPED;
			m_moveSpeed.z -= addSpeed.z * SARU_MOVE_SPPED;
		}
	}
	//サルのアニメーション
	switch (m_enAnimClip)
	{
	case Saru::enAnim_wait:			//待機アニメーション
		m_animation.Play(enAnim_wait, m_animTime);
		break;
	case Saru::enAnim_run:			//走りアニメーション
		m_animation.Play(enAnim_run, m_animTime);
		break;
	case Saru::enAnim_attack:		//攻撃アニメーション
		m_animation.Play(enAnim_attack, m_animTime);
		break;
	case Saru::enAnim_Get:			//捕獲アニメーション
		m_animation.Play(enAnim_Get, m_animTime);
		break;
	case enState_stun:				//怯みアニメーション
		m_animation.Play(enAnim_Get, m_animTime);
		break;
	case enState_found:				//見つかったアニメーション
		m_animation.Play(enAnim_found, m_animTime);
		break;
	}

	//アニメーションの更新。
	m_animation.Update(GameTime().GetFrameDeltaTime());

	//シャドウキャスターを設定
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

void Saru::Move()
{
	CVector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.Normalize();

	m_moveSpeed.x = moveSpeedXZ.x * SARU_MOVE_SPPED;
	m_moveSpeed.z = moveSpeedXZ.z * SARU_MOVE_SPPED;

	Turn();
}

void Saru::Run()
{
	CVector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.Normalize();

	m_moveSpeed.x = moveSpeedXZ.x * SARU_RUN_SPPED;
	m_moveSpeed.z = moveSpeedXZ.z * SARU_RUN_SPPED;

	Turn();
}

void Saru::GetSaru()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	m_enSaruState = enState_Get;
}

void Saru::Turn()
{
	CVector3 toSaruDir = m_pl->GetPos() - m_position;

	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	m_angle = atan2f(-toSaruDir.x, -toSaruDir.z);
	m_rotation.SetRotation(CVector3::AxisY(), m_angle);
}

void Saru::BanaPeelThrow()
{
	CVector3 saruFoward = CVector3::Back();
	m_rotation.Multiply(saruFoward);

	CVector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;

	//バナナの皮を投げる
	m_banaPeelTimer++;
	if (moveSpeedXZ.LengthSq() >= 1.0f * 1.0f && m_banaPeelTimer > SARU_BANANAPEEL_TIME) {
		m_banaPeel = NewGO<BananaPeel>();
		m_banaPeel->SetPlayer(m_pl);
		m_banaPeel->SetMoveSpd(saruFoward);
		m_banaPeel->SetPosition(m_position);
		m_banaPeelTimer = 0;
	}
}

void Saru::Stun()
{
	m_enSaruState = enState_stun;
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
}

void Saru::Found()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	CVector3 positionY = m_position;
	positionY.y = m_position.y + SARU_BIKKURIMARK_POSITION_Y;

	m_bikkuriMark->SetPosition(positionY);

	//サルからプレイヤーに伸びるベクトルを求める。
	CVector3 toSaruDir = m_pl->GetPos() - m_position;
	//プレイヤーの方を見る
	m_angle = atan2f(toSaruDir.x, toSaruDir.z);
	m_rotation.SetRotation(CVector3::AxisY(),m_angle);

	if (m_animation.IsPlaying() != true) {
		DeleteGO(m_bikkuriMark);
		m_enSaruState = enState_run;
	}
}

void Saru::AttackDistance()
{
	//サルからプレイヤーに伸びるベクトルを求める。
	CVector3 toSaruDir = m_pl->GetPos() - m_position;
	float toSaruLen = toSaruDir.Length();

	if (toSaruLen < SARU_ATTACK_DISTANCE) {
		m_enSaruState = enState_attack;
	}
}

void Saru::Death()
{
	DeleteGO(this);
	m_pl->DeleteSaru(this);
}

void Saru::ChangeStateWaitAnim()
{
	if (m_animation.IsPlaying() != true) {
		m_enSaruState = enState_wait;
	}
}

void Saru::SaruGetSound()
{
	//サウンドを再生
	prefab::CSoundSource* saruGetSE = NewGO<prefab::CSoundSource>();
	saruGetSE->Init(L"Assets/Sound/SaruSE_Get.wav");
	saruGetSE->Play(false);
}

void Saru::SaruFoundSound()
{
	//ビックリマークを生成。
	m_bikkuriMark = NewGO<BikkuriMark>();

	//サウンドを再生
	prefab::CSoundSource* saruSE_Found = NewGO<prefab::CSoundSource>();
	saruSE_Found->Init(L"Assets/Sound/SaruSE_Found.wav");
	saruSE_Found->Play(false);
}

void Saru::SaruAttackSound()
{
	//サウンドを再生
	prefab::CSoundSource* saruSE_Attack = NewGO<prefab::CSoundSource>();
	saruSE_Attack->Init(L"Assets/Sound/SaruSE_Attack.wav");
	saruSE_Attack->Play(false);
}

void Saru::SaruStunSound()
{
	//サウンドを再生
	prefab::CSoundSource* saruSE_Stun = NewGO<prefab::CSoundSource>();
	saruSE_Stun->Init(L"Assets/Sound/SaruSE_Stun.wav");
	saruSE_Stun->Play(false);
	saruSE_Stun->SetVolume(SARU_STUN_SE_VOLUME);
}

void Saru::ChangeState(EnSaruState nextState)
{
	ISaruState* pNextState = nullptr;
	EnAnimationClip nextAnimClip = enAnim_wait;
	switch (nextState)
	{
	case Saru::enState_wait:
		//現在の状態を待機状態にする。
		pNextState = &m_saruStateWait;
		nextAnimClip = enAnim_wait;
		break;
	case Saru::enState_run:
		//現在の状態を走り状態にする。
		pNextState = &m_saruStateRun;
		nextAnimClip = enAnim_run;
		break;
	case Saru::enState_attack:
		//現在の状態を攻撃状態にする。
		pNextState = &m_saruStateAttack;
		nextAnimClip = enAnim_attack;
		break;
	case Saru::enState_Get:
		//現在の状態を捕獲状態にする。
		pNextState = &m_saruStateGet;
		nextAnimClip = enAnim_Get;
		break;
	case Saru::enState_stun:
		//現在の状態を怯み状態にする。
		pNextState = &m_saruStateStun;
		nextAnimClip = enAnim_Get;
		break;
	case Saru::enState_found:
		//現在の状態を見つかった状態にする。
		pNextState = &m_saruStateFound;
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