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
	Move();

	m_moveSpeed.y -= 100.0f;

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

		CVector3 eneFoward = CVector3::AxisZ();
		//エネミーからプレイヤーに伸びるベクトルを求める。
		CVector3 toEnemyDir = m_saru->GetPos() - m_position;
		float toEnemyLen = toEnemyDir.Length();
		toEnemyDir.Normalize();

		float d = eneFoward.Dot(toEnemyDir);
		float angle = acos(d);

		if (fabsf(angle) < CMath::DegToRad(45.0f) && toEnemyLen < 80.0f)
		{
			m_saru->GetSaru();
		}

		break;
	}

	
}

void Player::Move()
{
	m_moveSpeed.x = g_pad[0].GetLStickXF() * 1000.0f;
	m_moveSpeed.z = g_pad[0].GetLStickYF() * 1000.0f;

	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
}

void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}