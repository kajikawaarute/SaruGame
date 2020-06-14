#include "stdafx.h"
#include "Saru.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "BananaPeel.h"

const float SARU_MOVE_SPPED = 1200.0f;	//サルの移動速度。
const float SARU_FUTTOBI_POWER = 1000.0f;

Saru::Saru()
{
	m_model.Init(L"Assets/modelData/Saru.cmo");

	//アニメーションをロード
	m_animClip[enAnim_wait].Load(L"Assets/animData/Saru-taiki.tka");
	m_animClip[enAnim_run].Load(L"Assets/animData/Saru-run.tka");
	m_animClip[enAnim_attack].Load(L"Assets/animData/Saru-Attack.tka");
	m_animClip[enAnim_Get].Load(L"Assets/animData/Saru-Get.tka");
	m_animClip[enAnim_found].Load(L"Assets/animData/Saru-found.tka");

	//エフェクトをロード
	m_effekt = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/SaruGet.efk");

	//アニメーションのループを設定
	m_animClip[enAnim_wait].SetLoopFlag(true);
	m_animClip[enAnim_run].SetLoopFlag(true);

	//サルの初期アニメーション
	m_enAnimClip = enAnim_wait;

	//サルの初期状態
	m_currentState = &m_saruStateWait;

	//アニメーションの初期化
	m_animation.Init(m_model, m_animClip, enAnim_num);

	//状態を初期化する。
	m_saruStateWait.Init(this);
	m_saruStateRun.Init(this);
	m_saruStateAttack.Init(this);
	m_saruStateGet.Init(this);
	m_saruStateStun.Init(this);
	m_saruStateFound.Init(this);

	//サウンドソースの初期化
	/*m_saru_getAmiSE.Init(L"Assets/Sound/SaruSE_Get.wav");
	m_saru_attackSE.Init(L"Assets/Sound/SaruSE_Attack.wav");*/
}

Saru::~Saru()
{
}

void Saru::Update()
{
	//エネミ−の状態
	m_currentState->Update();
	ChangeState(m_enSaruState);

	//サルのアニメーション
	switch (m_enAnimClip)
	{
	case Saru::enAnim_wait:		//待機アニメーション
		m_animation.Play(enAnim_wait, m_animTime);
		break;
	case Saru::enAnim_run:			//走りアニメーション
		m_animation.Play(enAnim_run, m_animTime);
		break;
	case Saru::enAnim_attack:		//攻撃アニメーション
		//m_saru_attackSE.Play(false);
		m_animation.Play(enAnim_attack, m_animTime);
		break;
	case Saru::enAnim_Get:			//捕獲アニメーション
		//m_saru_getAmiSE.Play(false);
		m_animation.Play(enAnim_Get, m_animTime);
		break;
	case enState_stun:
		m_animation.Play(enAnim_Get, m_animTime);
		break;
	case enState_found:				//見つかったアニメーション
		m_animation.Play(enAnim_found, m_animTime);
		break;
	}

	m_animation.Update(GameTime().GetFrameDeltaTime());
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Saru::Move()
{
	m_moveSpeed.Normalize();
	m_moveSpeed.x *= SARU_MOVE_SPPED;
	m_moveSpeed.z *= SARU_MOVE_SPPED;
	m_moveSpeed.y = 0.0f;
	m_position -= m_moveSpeed * GameTime().GetFrameDeltaTime();

	Turn();
}

void Saru::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Saru::GetSaru()
{
	m_enSaruState = enState_Get;
	m_deathTimer++;
	if (m_deathTimer == 1) {
		//エフェクトを再生。
		m_playEffectHandle = g_effekseerManager->Play(m_effekt, m_position.x, m_position.y, m_position.z);
	}
	if (m_deathTimer == 40) {
		g_goMgr.DeleteGO(this);
		m_pl->DeleteSaru(this);
	}
}

void Saru::Turn()
{
	CVector3 toSaruDir = m_pl->GetPos() - m_position;

	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}

	m_rotation.SetRotation(CVector3::AxisY(), atan2f(-toSaruDir.x, -toSaruDir.z));
}

void Saru::BanaPeelThrow()
{
	CVector3 saruFoward = CVector3::Back();
	m_rotation.Multiply(saruFoward);

	CVector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;

	//バナナの皮を投げる
	m_banaPeelTimer++;
	if (moveSpeedXZ.LengthSq() >= 1.0f * 1.0f && m_banaPeelTimer > 90) {
		m_banaPeel = g_goMgr.NewGO<BananaPeel>();
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
	if (m_animation.IsPlaying() != true) {
		m_enSaruState = enState_wait;
	}
}

void Saru::Found()
{
	//サルからプレイヤーに伸びるベクトルを求める。
	CVector3 toSaruDir = m_pl->GetPos() - m_position;
	//プレイヤーの方を見る
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toSaruDir.x, toSaruDir.z));

	if (m_animation.IsPlaying() != true) {
		m_enSaruState = enState_run;
	}
}

void Saru::AttackDistance()
{
	//サルからプレイヤーに伸びるベクトルを求める。
	CVector3 toSaruDir = m_pl->GetPos() - m_position;
	float toSaruLen = toSaruDir.Length();

	if (toSaruLen < 90.0f) {
		m_enSaruState = enState_attack;
	}
}

void Saru::Attack()
{
	//サルからプレイヤーに伸びるベクトルを求める。
	CVector3 toSaruDir = m_pl->GetPos() - m_position;
	//プレイヤーの方を見る
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toSaruDir.x, toSaruDir.z));
	
	toSaruDir.Normalize();
	m_pl->SetAttackedPower(toSaruDir * SARU_FUTTOBI_POWER);
	m_pl->Attacked();
}

void Saru::Death()
{
	g_goMgr.DeleteGO(this);
	m_pl->DeleteSaru(this);
}

void Saru::ChangeStateWaitAnim()
{
	if (m_animation.IsPlaying() != true) {
		m_enSaruState = enState_wait;
	}
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
	}
	//開始処理
	m_currentState->OnEnter();
}