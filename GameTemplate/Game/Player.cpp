#include "stdafx.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "Saru.h"
#include "Enemy.h"

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/Player.cmo");

	//キャラクターコントローラーの初期化
	m_charaCon.Init(50.0f, 100.0f, m_position);
	
	//ぷれいやーのアニメーションをロード
	m_animationClip[enAnim_walk].Load(L"Assets/animData/Player-walk.tka");
	m_animationClip[enAnim_taiki].Load(L"Assets/animData/Player-taiki.tka");
	m_animationClip[enAnim_saruGet].Load(L"Assets/animData/Player-SaruGet.tka");
	m_animationClip[enAnim_attacked].Load(L"Assets/animData/Player-attacked.tka");
	m_animationClip[enAnim_jump].Load(L"Assets/animData/Player-jump.tka");
	m_animationClip[enAnim_sliped].Load(L"Assets/animData/Player-Slip.tka");
	m_animationClip[enAnim_attack].Load(L"Assets/animData/Player-attack.tka");

	m_animationClip[enAnim_walk].SetLoopFlag(true);
	m_animationClip[enAnim_taiki].SetLoopFlag(true);

	//アニメーションを初期化
	m_animation.Init(m_model, m_animationClip, enAnim_num);

	//サウンドソースを初期化
	//m_player_walkSE = g_goMgr.NewGO<prefab::CSoundSource>();
	
	//m_player_AmiSE.Init(L"Assets/Sound/PlayerSE_Ami.wav");
	//m_player_walkSE.Init(L"Assets/Sound/PlayerSE_walk.wav");
	//m_player_JumpSE.Init(L"Assets/Sound/PlayerSE_Jump.wav");

	//プレイヤーの初期アニメーション
	m_enAnimClip = enAnim_taiki;

	//プレイヤーの初期状態
	m_enPlayerState = enState_taiki;

	m_ghost.CreateBox({1700.0f, 0.0f, -100.0f}, CQuaternion::Identity(), { 300.0f, 30.0f, 200.0f });
}


Player::~Player()
{
	m_ghost.Release();
}

void Player::Update()
{
	m_moveSpeed.y -= 50.0f;

	g_physics.ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
		if (m_ghost.IsSelf(contactObject) == true) {
			m_moveSpeed.y = 3000.0f;
		}
		});

	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	CVector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;

	//プレイヤーの状態
	switch (m_enPlayerState)
	{
	case enState_taiki:		//待機状態
		Move();
		Jump();
		SaruGet();
		AttackTry();
		m_enAnimClip = enAnim_taiki;
		if (moveSpeedXZ.LengthSq() >= 1.0f * 1.0f) {
			m_enPlayerState = enState_walk;
		}
		break;
	case enState_walk:		//歩き状態
		Move();
		Jump();
		SaruGet();
		AttackTry();
		m_enAnimClip = enAnim_walk;
		if (moveSpeedXZ.LengthSq() <= 1.0f * 1.0f) {
			m_enPlayerState = enState_taiki;
		}
		break;
	case enState_saruGet:	//サルを捕獲
		GetSaru();
		m_enAnimClip = enAnim_saruGet;
		m_saruGet_taikiTimer++;
		if (m_saruGet_taikiTimer == 40) {
			m_enPlayerState = enState_taiki;
			m_saruGet_taikiTimer = 0;
		}
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		break;
	case enState_attacked:	//攻撃された状態
		m_enAnimClip = enAnim_attacked;
		break;
	case enState_Jump:		//ジャンプ状態
		m_enAnimClip = enAnim_jump;
		Move();
		SaruGet();
		if (m_charaCon.IsOnGround()) {
			m_enPlayerState = enState_taiki;
		}
		break;
	case enState_sliped:		//滑っている状態
		m_enAnimClip = enAnim_sliped;
		Sliped();
		m_slipTime++;
		if (m_slipTime == 90) {
			m_enPlayerState = enState_taiki;
			m_slipTime = 0;
		}
		break;
	case enState_attack:		//攻撃状態
		Attack();
		m_enAnimClip = enAnim_attack;
		m_attack_taikiTimer++;
		if (m_attack_taikiTimer == 25) {
			m_enPlayerState = enState_taiki;
			m_attack_taikiTimer = 0;
		}
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
		break;
	}

	//プレイヤーのアニメーション
	switch (m_enAnimClip)
	{
	case enAnim_taiki:		//待機アニメーション
		m_animation.Play(enAnim_taiki, animTime);
		break;
	case enAnim_walk:		//歩きアニメーション
		//m_player_walkSE.Play(false);
		m_animation.Play(enAnim_walk, animTime);
		break;
	case enAnim_saruGet:	//サルの捕獲アニメーション
		m_animation.Play(enAnim_saruGet, animTime);
		break;
	case enAnim_attacked:	//攻撃されたときのアニメーション
		m_animation.Play(enAnim_attacked, animTime);
		break;
	case enAnim_jump:		//ジャンプアニメーション
		m_animation.Play(enAnim_jump, animTime);
		break;
	case enAnim_sliped:		//滑っている時のアニメーション
		m_animation.Play(enAnim_sliped, animTime);
		break;
	case enAnim_attack:		//攻撃アニメーション
		m_animation.Play(enAnim_attack, animTime);
		break;
	}

	m_animation.Update(1.0f / 30.0f);
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
	m_moveSpeed.x = cameraForward.x * StickZ;
	m_moveSpeed.z = cameraForward.z * StickZ;

	CVector3 cameraRight;
	cameraRight.Cross({ 0.0f, 1.0f, 0.0f }, cameraForward);
	cameraRight.Normalize();
	m_moveSpeed += cameraRight * StickX;

	Turn();
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
	m_rotation.Multiply(plFoward);
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

void Player::Turn()
{
	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);

	m_rotation.SetRotation(CVector3::AxisY(), angle);
}

void Player::DeleteSaru(Saru* saru)
{
	for (auto it = m_sarus.begin(); it != m_sarus.end();) {
		if (*it == saru) {
			it = m_sarus.erase(it);
			m_saruCount++;
			//it++;
		}
		else {
			//リクエストを受けていない。
			it++;
		}
	}
}

void Player::DeleteEnemy(Enemy * enemy)
{
	for (auto it = m_enemys.begin(); it != m_enemys.end();) {
		if (*it == enemy) {
			it = m_enemys.erase(it);
			//it++;
		}
		else {
			//リクエストを受けていない。
			it++;
		}
	}
}

void Player::Attacked()
{
	m_enPlayerState = enState_attacked;

	m_attacked_taikiTimer++;
	if (m_attacked_taikiTimer == 60) {
		m_enPlayerState = enState_taiki;
		m_attacked_taikiTimer = 0;
	}
}

void Player::Sliped()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), 5.0f);
	m_rotation.Multiply(addRot);
}

void Player::Jump()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{
		/*prefab::CSoundSource* player_JumpSE = g_goMgr.NewGO<prefab::CSoundSource>();
		player_JumpSE->Init(L"Assets/Sound/PlayerSE_Jump.wav");
		player_JumpSE->Play(false);*/

		m_moveSpeed.y = 1000.0f;
		m_enPlayerState = enState_Jump;
	}
}

void Player::SaruGet()
{
	if (g_pad[0].IsTrigger(enButtonB))
	{
		/*prefab::CSoundSource* player_AmiSE = g_goMgr.NewGO<prefab::CSoundSource>();
		player_AmiSE->Init(L"Assets/Sound/PlayerSE_Ami.wav");
		player_AmiSE->Play(false);*/
		m_enPlayerState = enState_saruGet;
	}
}

void Player::AttackTry()
{
	if (g_pad[0].IsTrigger(enButtonX))
	{
		m_enPlayerState = enState_attack;
	}
}

void Player::Attack()
{
	CVector3 plFoward = CVector3::AxisZ();
	m_rotation.Multiply(plFoward);
	//サルからプレイヤーに伸びるベクトルを求める。
	for (int i = 0; i < m_enemys.size(); i++) {
		CVector3 toPlayerDir = m_enemys[i]->GetPos() - m_position;
		float toEnemyLen = toPlayerDir.Length();
		toPlayerDir.Normalize();

		float d = plFoward.Dot(toPlayerDir);
		float angle = acos(d);

		if (fabsf(angle) < CMath::DegToRad(45.0f) && toEnemyLen < 100.0f)
		{
			m_enemys[i]->Delete();
		}
	}
}

void Player::SetPlayerWalkSE()
{
	/*prefab::CSoundSource* m_player_walkSE = g_goMgr.NewGO<prefab::CSoundSource>();
	m_player_walkSE->Init(L"Assets/Sound/PlayerSE_walk.wav");
	m_player_walkSE->Play(false);*/
}
