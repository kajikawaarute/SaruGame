#include "stdafx.h"
#include "Saru.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "BananaPeel.h"

Saru::Saru()
{
	m_model.Init(L"Assets/modelData/Saru.cmo");

	//アニメーションをロード
	m_animClip[enAnim_taiki].Load(L"Assets/animData/Saru-taiki.tka");
	m_animClip[enAnim_run].Load(L"Assets/animData/Saru-run.tka");
	m_animClip[enAnim_attack].Load(L"Assets/animData/Saru-Attack.tka");
	m_animClip[enAnim_Get].Load(L"Assets/animData/Saru-Get.tka");

	m_animClip[enAnim_taiki].SetLoopFlag(true);
	m_animClip[enAnim_run].SetLoopFlag(true);

	//サルの初期アニメーション
	m_enAnimClip = enAnim_taiki;

	//サルの初期状態
	m_enSaruState = enSaru_taiki;

	m_animation.Init(m_model, m_animClip, enAnim_num);

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
	Turn();

	if (g_pad[0].IsTrigger(enButtonA)) {
		BananaPeel* banaPeel = g_goMgr.NewGO<BananaPeel>();
		banaPeel->SetPosition(m_position);
	}

	CVector3 saruFoward = CVector3::AxisZ();
	m_rotation.Multiply(saruFoward);
	//サルからプレイヤーに伸びるベクトルを求める。
	CVector3 toSaruDir = m_pl->GetPos() - m_position;
	float toSaruLen = toSaruDir.Length();
	toSaruDir.Normalize();

	float d = saruFoward.Dot(toSaruDir);

	float angle = acos(d);

	//サルの状態
	switch (m_enSaruState)
	{
	case Saru::enSaru_taiki:	//待機状態
		Move();
		m_enAnimClip = enAnim_taiki;
		m_moveSpeed = CVector3::Zero();
		if (fabsf(angle) < CMath::DegToRad(90.0f) && toSaruLen < 500.0f)
		{
			m_enSaruState = enSaru_run;
		}
		Angle();
		break;
	case Saru::enSaru_run:		//走り状態
		Move();
		m_enAnimClip = enAnim_run;
		m_moveSpeed = toSaruDir;
		if (toSaruLen > 700.0f)
		{
			m_enSaruState = enSaru_taiki;
		}
		Angle();
		break;
	case Saru::enSaru_attack:	//攻撃状態
		m_enAnimClip = enAnim_attack;

		m_rotation.SetRotation(CVector3::AxisY(), atan2f(toSaruDir.x, toSaruDir.z));

		m_moveSpeed = CVector3::Zero();
		m_timer++;
		m_pl->Fukitobi();
		if (m_timer == 60) {
			m_enSaruState = enSaru_taiki;
			m_enAnimClip = enAnim_taiki;
			m_timer = 0;
		}
		break;
	case Saru::enSaru_Get:		//捕獲状態
		m_enAnimClip = enAnim_Get;
		break;
	}

	//サルのアニメーション
	switch (m_enAnimClip)
	{
	case Saru::enAnim_taiki:		//待機アニメーション
		m_animation.Play(enAnim_taiki);
		break;
	case Saru::enAnim_run:			//走りアニメーション
		m_animation.Play(enAnim_run);
		break;
	case Saru::enAnim_attack:		//攻撃アニメーション
		m_animation.Play(enAnim_attack);
		break;
	case Saru::enAnim_Get:			//捕獲アニメーション
		m_animation.Play(enAnim_Get);
		break;
	}

	CVector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	if (toSaruLen > 100.0f && moveSpeedXZ.LengthSq() >= 1.0f * 1.0f && m_bananaCount == 0) {
		BananaPeel* banaPeel = g_goMgr.NewGO<BananaPeel>();
		banaPeel->SetPosition(m_position);
		m_bananaCount++;
	}

	EffekseerCamera();

	m_animation.Update(1.0f / 30.0f);
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

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
	m_enSaruState = enSaru_Get;
	m_deathTimer++;
	if (m_deathTimer == 1) {
		//エフェクトを再生。
		m_playEffectHandle = m_effekseerManager->Play(m_effekt, m_position.x, m_position.y, m_position.z);
	}
	if (m_deathTimer == 60) {
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

void Saru::Angle()
{
	//サルからプレイヤーに伸びるベクトルを求める。
	CVector3 toSaruDir = m_pl->GetPos() - m_position;
	float toSaruLen = toSaruDir.Length();

	if (toSaruLen < 90.0f) {
		m_enSaruState = enSaru_attack;
	}
}
