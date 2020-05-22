#include "stdafx.h"
#include "Saru.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "BananaPeel.h"

Saru::Saru()
{
	m_model.Init(L"Assets/modelData/Saru.cmo");

	//アニメーションをロード
	m_animClip[enAnim_wait].Load(L"Assets/animData/Saru-taiki.tka");
	m_animClip[enAnim_run].Load(L"Assets/animData/Saru-run.tka");
	m_animClip[enAnim_attack].Load(L"Assets/animData/Saru-Attack.tka");
	m_animClip[enAnim_Get].Load(L"Assets/animData/Saru-Get.tka");

	//アニメーションのループを設定
	m_animClip[enAnim_wait].SetLoopFlag(true);
	m_animClip[enAnim_run].SetLoopFlag(true);

	//サルの初期アニメーション
	m_enAnimClip = enAnim_wait;

	//サルの初期状態
	m_currentState = &m_saruStateWait;

	//アニメーションの初期化
	m_animation.Init(m_model, m_animClip, enAnim_num);

	//サウンドソースの初期化
	/*m_saru_getAmiSE.Init(L"Assets/Sound/SaruSE_Get.wav");
	m_saru_attackSE.Init(L"Assets/Sound/SaruSE_Attack.wav");*/

	//Effekseerを初期化。
	InitEffekseer();
	//エフェクトをロード
	m_effekt = Effekseer::Effect::Create(m_effekseerManager, (const EFK_CHAR*)L"Assets/effect/SaruGet.efk");
}

Saru::~Saru()
{
}

void Saru::Update()
{
	//エネミ－の状態
	m_currentState->Init(this);
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
	}

	m_animation.Update(1.0f / 30.0f);
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	EffekseerCamera();
	//Effekseerを更新
	m_effekseerManager->Update();
}

void Saru::Move()
{
	m_moveSpeed.Normalize();
	m_moveSpeed.x *= 5.0f;
	m_moveSpeed.z *= 5.0f;
	m_moveSpeed.y = 0.0f;
	m_position -= m_moveSpeed;

	Turn();
}

void Saru::Draw()
{
	m_effekseerRenderer->BeginRendering();
	m_effekseerManager->Draw();
	m_effekseerRenderer->EndRendering();

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
		m_playEffectHandle = m_effekseerManager->Play(m_effekt, m_position.x, m_position.y, m_position.z);
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

void Saru::InitEffekseer()
{
	//レンダラーを初期化。
	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3Dデバイス。
		g_graphicsEngine->GetD3DDeviceContext(),	//D3Dデバイスコンテキスト。
		20000										//板ポリの最大数。
	);
	//エフェクトマネージャを初期化。
	m_effekseerManager = Effekseer::Manager::Create(10000);

	// 描画用インスタンスから描画機能を設定
	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());
}

void Saru::EffekseerCamera()
{
	//Effekseerカメラ行列を設定。
	//まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
	Effekseer::Matrix44 efCameraMat;
	g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
	Effekseer::Matrix44 efProjMat;
	g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
	//カメラ行列とプロジェクション行列を設定。
	m_effekseerRenderer->SetCameraMatrix(efCameraMat);
	m_effekseerRenderer->SetProjectionMatrix(efProjMat);
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

	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toSaruDir.x, toSaruDir.z));

	m_pl->GetMoveSpd() = toSaruDir * 2.0f;

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
	if (m_currentState != nullptr) {
		//終了処理
		m_currentState->OnLeave();
	}
	switch (nextState)
	{
	case Saru::enState_wait:
		//現在の状態を待機状態にする。
		m_currentState = &m_saruStateWait;
		m_enAnimClip = enAnim_wait;
		break;
	case Saru::enState_run:
		//現在の状態を走り状態にする。
		m_currentState = &m_saruStateRun;
		m_enAnimClip = enAnim_run;
		break;
	case Saru::enState_attack:
		//現在の状態を攻撃状態にする。
		m_currentState = &m_saruStateAttack;
		m_enAnimClip = enAnim_attack;
		break;
	case Saru::enState_Get:
		//現在の状態を捕獲状態にする。
		m_currentState = &m_saruStateGet;
		m_enAnimClip = enAnim_Get;
		break;
	case Saru::enState_stun:
		//現在の状態を怯み状態にする。
		m_currentState = &m_saruStateStun;
		m_enAnimClip = enAnim_Get;
		break;
	}
	//開始処理
	m_currentState->OnEnter();
}