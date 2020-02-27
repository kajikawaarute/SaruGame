#include "stdafx.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "Saru.h"

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/Player-kari.cmo");

	//キャラクターコントローラーの初期化
	m_charaCon.Init(50.0f, 100.0f, m_position);
	
	//ぷれいやーのアニメーションをロード
	m_animationClip[enAnim_walk].Load(L"Assets/animData/Player-kari-walk.tka");
	m_animationClip[enAnim_taiki].Load(L"Assets/animData/Player-kari-taiki.tka");
	m_animationClip[enAnim_saruGet].Load(L"Assets/animData/Player-kari-saruGet.tka");
	
	m_animationClip[enAnim_walk].SetLoopFlag(true);
	m_animationClip[enAnim_taiki].SetLoopFlag(true);

	//アニメーションを初期化
	m_animation.Init(m_model, m_animationClip, enAnim_num);

	m_enAnimClip = enAnim_taiki;

	m_ghost.CreateBox({1700.0f, 0.0f, -100.0f}, CQuaternion::Identity(), { 300.0f, 30.0f, 200.0f });
}


Player::~Player()
{
}

void Player::Update()
{

	if (m_flag == true) {
		Move();
	}
	else {
		m_flag = true;
	}
	m_moveSpeed.y -= 500.0f;
	Turn();

	g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghost.IsSelf(contactObject) == true) {
			m_moveSpeed.y = 3000.0f;
		}
		});

	if (g_pad[0].IsTrigger(enButtonA))
	{
		m_moveSpeed.y = 1000.0f;
	}

	if (g_pad[0].IsTrigger(enButtonB))
	{
		m_enAnimClip = enAnim_saruGet;
	}

	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotetion, m_scale);

	m_animation.Update(1.0f / 30.0f);

	CVector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	
	switch (m_enAnimClip)
	{
	case enAnim_taiki:
		m_animation.Play(enAnim_taiki);
		if (moveSpeedXZ.LengthSq() >= 1.0f * 1.0f) {
			m_enAnimClip = enAnim_walk;
		}
		break;
	case enAnim_walk:
		m_animation.Play(enAnim_walk);
		if (moveSpeedXZ.LengthSq() <= 1.0f * 1.0f) {
			m_enAnimClip = enAnim_taiki;
		}
		break;
	case enAnim_saruGet:
		m_animation.Play(enAnim_saruGet);
		m_timer++;
		if (m_timer == 60) {
			m_enAnimClip = enAnim_taiki;
			m_timer = 0;
		}
		GetSaru();
		break;
	}
}

void Player::Move()
{
	//m_moveSpeed.x = g_pad[0].GetLStickXF() * 1000.0f;
	//m_moveSpeed.z = g_pad[0].GetLStickYF() * 1000.0f;

	float StickZ = g_pad[0].GetLStickYF() * 1000.0f;
	float StickX = g_pad[0].GetLStickXF() * 1000.0f;

	CVector3 cameraForward = g_camera3D.GetTarget() - g_camera3D.GetPosition();
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	m_moveSpeed = cameraForward * StickZ;

	CVector3 cameraRight;
	cameraRight.Cross({ 0.0f, 1.0f, 0.0f }, cameraForward);
	cameraRight.Normalize();
	m_moveSpeed += cameraRight * StickX;
}

void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::GetSaru()
{
	CVector3 plFoward = CVector3::AxisZ();
	m_rotetion.Multiply(plFoward);
	//サルからプレイヤーに伸びるベクトルを求める。
	for (int i = 0; i < m_sarus.size(); i++) {
		CVector3 toPlayerDir = m_sarus[i]->GetPos() - m_position;
		float toEnemyLen = toPlayerDir.Length();
		toPlayerDir.Normalize();

		float d = plFoward.Dot(toPlayerDir);
		float angle = acos(d);

		if (fabsf(angle) < CMath::DegToRad(45.0f) && toEnemyLen < 100.0f)
		{
			m_sarus[i]->GetSaru();
		}
	}
}

void Player::Fukitobi()
{
	for (int i = 0; i < m_sarus.size(); i++)
	{
		CVector3 toPlayerDir = m_sarus[i]->GetPos() - m_position;
		m_moveSpeed = toPlayerDir * -1.0f;
	}
	
	m_flag = false;
}

void Player::Turn()
{
	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);

	m_rotetion.SetRotation(CVector3::AxisY(), angle);
}

void Player::DeleteSaru(Saru* saru)
{
	for (auto it = m_sarus.begin(); it != m_sarus.end();) {
		if (*it == saru) {
			it = m_sarus.erase(it);
			//it++;
		}
		else {
			//リクエストを受けていない。
			it++;
		}
	}
}
