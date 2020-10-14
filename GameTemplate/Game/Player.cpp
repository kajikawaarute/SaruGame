#include "stdafx.h"
#include "Player.h"
#include "Saru.h"
#include "Enemy.h"
#include "GunEnemy.h"
#include "PlayerHP.h"
#include "IPlayerState.h"

const float PLAYER_GRAVITY = 5000.0f;		//プレイヤーにかかる重力(単位cm/秒)。
const float PLAYER_JUMP_POWER = 2000.0f;	//プレイヤーがジャンプしたときに加算される速度。
const float PLAYER_MOVE_SPEED = 850.0f;		//プレイヤーの移動速度。
const float PLAYER_SARU_DISTANCE = 300.0f;	//プレイヤーとサルの距離。
const float PLAYER_SWORD_SE_VOLUME = 0.9f;	//プレイヤーが攻撃している時のSEのボリューム。

Player::Player()
{
	//キャラクターコントローラーの初期化
	m_charaCon.Init(50.0f, 100.0f, m_position);

	//プレイヤーの初期状態
	m_currentState = &m_playerStateWait;
}


Player::~Player()
{
	DeleteGO(m_skinModel);
}

bool Player::Start()
{
	//cmoファイルの読み込み。
	m_skinModel = NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/Player.cmo");

	//プレイヤーのアニメーションをロード
	m_animationClip[enAnim_walk].Load(L"Assets/animData/Player-walk.tka");
	m_animationClip[enAnim_wait].Load(L"Assets/animData/Player-taiki.tka");
	m_animationClip[enAnim_saruGet].Load(L"Assets/animData/Player-SaruGet.tka");
	m_animationClip[enAnim_attacked].Load(L"Assets/animData/Player-attacked2.tka");
	m_animationClip[enAnim_jump].Load(L"Assets/animData/Player-jump.tka");
	m_animationClip[enAnim_sliped].Load(L"Assets/animData/Player-Slip.tka");
	m_animationClip[enAnim_attack].Load(L"Assets/animData/Player-attack.tka");
	m_animationClip[enAnim_death].Load(L"Assets/animData/Player-death.tka");

	//アニメーションのループ設定。
	m_animationClip[enAnim_walk].SetLoopFlag(true);
	m_animationClip[enAnim_wait].SetLoopFlag(true);

	//アニメーションを初期化
	m_animation.Init(m_skinModel->GetSkinModel(), m_animationClip, enAnim_num);

	//プレイヤーの初期アニメーション
	m_enAnimClip = enAnim_wait;

	//シャドウレシーバーを設定。
	m_skinModel->SetShadowReciever();

	return true;
}

void Player::Update()
{
	//プレイヤーの重力
	m_moveSpeed.y -= PLAYER_GRAVITY *  GameTime().GetFrameDeltaTime();

	//プレイヤーの状態
	m_currentState->Init(this);
	m_currentState->Update();
	ChangeState(m_enPlayerState);

	//プレイヤーのアニメーション
	switch (m_enAnimClip)
	{
	case enAnim_wait:		//待機アニメーション
		m_animation.Play(enAnim_wait, animTime);
		break;
	case enAnim_walk:		//歩きアニメーション
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
	case enAnim_death:		//死亡アニメーション
		m_animation.Play(enAnim_death, animTime);
		break;
	}
	//アニメーションの更新。
	m_animation.Update(GameTime().GetFrameDeltaTime());

	//シャドウキャスターを設定。
	m_skinModel->SetShadowCaster();

	//シャドウマップの作成
	ShadowMap::GetInstance().UpdateShadowMap(
		m_position + CVector3::One() * 4000.0f,
		m_position
	);

	//トゥーンレンダーを設定。
	m_skinModel->SetToonRender();

	//キャラコンの更新。
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);

	//座標を設定。
	m_skinModel->SetPosition(m_position);

	//回転を設定。
	m_skinModel->SetRotation(m_rotation);
}

void Player::Move()
{
	float StickZ = g_pad[0].GetLStickYF() * PLAYER_MOVE_SPEED;
	float StickX = g_pad[0].GetLStickXF() * PLAYER_MOVE_SPEED;

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

		//サルを捕まえる範囲。
		if (fabsf(angle) < CMath::DegToRad(45.0f) && toEnemyLen < PLAYER_SARU_DISTANCE)
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
			m_enemyCount++;
		}
		else {
			//リクエストを受けていない。
			it++;
		}
	}
}

void Player::DeleteGunEnemy(GunEnemy * gunEnemy)
{
	for (auto it = m_gunEnemys.begin(); it != m_gunEnemys.end();) {
		if (*it == gunEnemy) {
			it = m_gunEnemys.erase(it);
			m_enemyCount++;
		}
		else {
			//リクエストを受けていない。
			it++;
		}
	}
}

void Player::Attacked()
{
	//攻撃を受けたフラグ
	m_playerHp->SetDamageFlag(true);
	m_enPlayerState = enState_attacked;

	//サウンドの再生。
	prefab::CSoundSource* playerSE_damage = NewGO<prefab::CSoundSource>();
	playerSE_damage->Init(L"Assets/Sound/PlayerSE_Damage.wav");
	playerSE_damage->Play(false);
}

void Player::Sliped()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//回転する。
	CQuaternion addRot;
	addRot.SetRotationDeg(CVector3::AxisY(), 5.0f);
	m_rotation.Multiply(addRot);
}

void Player::Jump()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{
		//ジャンプする
		m_moveSpeed.y = PLAYER_JUMP_POWER;
		m_enPlayerState = enState_Jump;

		//サウンドの再生。
		prefab::CSoundSource* playerSE_Jump = NewGO<prefab::CSoundSource>();
		playerSE_Jump->Init(L"Assets/Sound/PlayerSE_Jump.wav");
		playerSE_Jump->Play(false);
	}
}

void Player::SaruGet()
{
	if (g_pad[0].IsTrigger(enButtonX))
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;

		//サウンドの再生。
		prefab::CSoundSource* playerSE_Ami = NewGO<prefab::CSoundSource>();
		playerSE_Ami->Init(L"Assets/Sound/PlayerSE_Ami.wav");
		playerSE_Ami->Play(false);
		m_enPlayerState = enState_saruGet;
	}
	
}

void Player::AttackTry()
{
	if (g_pad[0].IsTrigger(enButtonB))
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;

		m_enPlayerState = enState_attack;

		//サウンドの再生。
		prefab::CSoundSource* playerSE_sword = NewGO<prefab::CSoundSource>();
		playerSE_sword->Init(L"Assets/Sound/PlayerSE_sword.wav");
		playerSE_sword->Play(false);
		playerSE_sword->SetVolume(PLAYER_SWORD_SE_VOLUME);
	}
}

void Player::StateDeath()
{
	m_enPlayerState = enState_death;
}

void Player::ChangeStateWaitAnim()
{
	if (m_animation.IsPlaying() != true) {
		m_enPlayerState = enState_wait;
	}
}

void Player::ChangeStateWaitIsOnGound()
{
	if (m_charaCon.IsOnGround()) {
		m_enPlayerState = enState_wait;
	}
}

void Player::ChangeState(EnPlayerState nextState)
{
	IPlayerState* pNextState = nullptr;
	EnAnimationClip nextAnimClip = enAnim_wait;
	switch (m_enPlayerState)
	{
	case Player::enState_wait:
		//現在の状態を待機状態にする。
		pNextState = &m_playerStateWait;
		nextAnimClip = enAnim_wait;
		break;
	case Player::enState_walk:
		//現在の状態を移動状態にする。
		pNextState = &m_playerStateMove;
		nextAnimClip = enAnim_walk;
		break;
	case Player::enState_saruGet:
		//現在の状態をサルを捕獲状態にする。
		pNextState = &m_playerStateSaruGet;
		nextAnimClip = enAnim_saruGet;
		break;
	case Player::enState_attacked:
		//現在の状態を攻撃された状態にする。
		pNextState = &m_playerStateAttacked;
		nextAnimClip = enAnim_attacked;
		break;
	case Player::enState_Jump:
		//現在の状態をジャンプ状態にする。
		pNextState = &m_playerStateJump;
		nextAnimClip = enAnim_jump;
		break;
	case Player::enState_sliped:
		//現在の状態を滑っている状態にする。
		pNextState = &m_playerStateSliped;
		nextAnimClip = enAnim_sliped;
		break;
	case Player::enState_attack:
		//現在の状態を攻撃状態にする。
		pNextState = &m_playerStateAttack;
		nextAnimClip = enAnim_attack;
		break;
	case Player::enAnim_death:
		//現在の状態を死亡状態にする。
		pNextState = &m_playerStateDeath;
		nextAnimClip = enAnim_death;
		break;
	}
	if (pNextState != nullptr && pNextState != m_currentState) {
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
