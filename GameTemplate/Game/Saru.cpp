#include "stdafx.h"
#include "Saru.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "BananaPeel.h"

Saru::Saru()
{
	m_model.Init(L"Assets/modelData/Saru.cmo");

	m_animClip[enAnim_taiki].Load(L"Assets/animData/Saru-taiki.tka");
	m_animClip[enAnim_run].Load(L"Assets/animData/Saru-run.tka");
	m_animClip[enAnim_attack].Load(L"Assets/animData/Saru-Attack.tka");

	m_animClip[enAnim_taiki].SetLoopFlag(true);
	m_animClip[enAnim_run].SetLoopFlag(true);

	m_enAnimClip = enAnim_taiki;

	m_animation.Init(m_model, m_animClip, enAnim_num);
}

Saru::~Saru()
{
}

void Saru::Update()
{
	Move();
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

	if (toSaruLen < 100.0f) {
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(toSaruDir.x, toSaruDir.z));
		m_enAnimClip = enAnim_attack;
	}

	switch (m_enAnimClip)
	{
	case Saru::enAnim_taiki:
		m_animation.Play(enAnim_taiki);
		m_moveSpeed = CVector3::Zero();
		if (fabsf(angle) < CMath::DegToRad(90.0f) && toSaruLen < 500.0f)
		{
			m_enAnimClip = enAnim_run;
		}
		break;
	case Saru::enAnim_run:
		m_animation.Play(enAnim_run);
		m_moveSpeed = toSaruDir;
		if (toSaruLen > 700.0f)
		{
			m_enAnimClip = enAnim_taiki;
		}
		break;
	case Saru::enAnim_attack:
		m_animation.Play(enAnim_attack);
		m_moveSpeed = CVector3::Zero();
		m_timer++;
		m_pl->Fukitobi();
		if (m_timer == 60) {
			m_enAnimClip = enAnim_taiki;
			m_timer = 0;
		}
		break;
	}

	CVector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	if (toSaruLen > 100.0f && moveSpeedXZ.LengthSq() >= 1.0f * 1.0f && m_bananaCount == 0) {
		BananaPeel* banaPeel = g_goMgr.NewGO<BananaPeel>();
		banaPeel->SetPosition(m_position);
		m_bananaCount++;
	}

	m_animation.Update(1.0f / 30.0f);
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
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
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Saru::GetSaru()
{
	g_goMgr.DeleteGO(this);
	m_pl->DeleteSaru(this);
}

void Saru::Turn()
{
	CVector3 toSaruDir = m_pl->GetPos() - m_position;

	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}

	m_rotation.SetRotation(CVector3::AxisY(), atan2f(-toSaruDir.x, -toSaruDir.z));
}