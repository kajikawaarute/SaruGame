#include "stdafx.h"
#include "JumpFloor.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

const float FLOOR_JUMP_POWER = 4000.0f;		//ジャンプ台ジャンプパワー。
JumpFloor::JumpFloor()
{
	//モデルの初期化。
	m_skinModel = g_goMgr.NewGO <SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/JumpFloor2.cmo");

	//アニメーションをロード
	m_animationClip[enAnim_wait].Load(L"Assets/animData/JumpFloor-wait.tka");
	m_animationClip[enAnim_jump].Load(L"Assets/animData/JumpFloor-jump.tka");

	//初期アニメーションを設定
	m_enAnimClip = enAnim_wait;

	//アニメーションを初期化
	m_animation.Init(m_skinModel->GetSkinModel(), m_animationClip, enAnim_num);

	//ゴーストオブジェクトを生成。
	m_ghost.CreateBox(m_position, m_rotation, m_ghostObjectScale);

	//シャドウレシーバーを設定。
	m_skinModel->SetShadowReciever();
}


JumpFloor::~JumpFloor()
{
	//スキンモデルを削除。
	g_goMgr.DeleteGO(m_skinModel);
}

void JumpFloor::Update()
{
	//ゴーストオブジェクトの判定。
	g_physics.ContactTest(m_player->GetcharaCon(), [&](const btCollisionObject& contactObject) {
		if (m_ghost.IsSelf(contactObject)) {
			prefab::CSoundSource* jumpFloorSE = g_goMgr.NewGO<prefab::CSoundSource>();
			jumpFloorSE->Init(L"Assets/Sound/JumpFloorSE.wav");
			jumpFloorSE->Play(false);
			m_player->GetMoveSpd().y = FLOOR_JUMP_POWER;
			m_enAnimClip = enAnim_jump;
		}
		});

	//ジャンプ台のアニメーション
	switch (m_enAnimClip)
	{
	case JumpFloor::enAnim_wait:
		m_animation.Play(enAnim_wait);
		break;
	case JumpFloor::enAnim_jump:
		m_animation.Play(enAnim_jump);
		break;
	}

	if (m_animation.IsPlaying() != true) {
		m_enAnimClip = enAnim_wait;
	}

	//アニメーションの更新。
	m_animation.Update(1.0f / 30.0f);

	//トゥーンレンダを設定。
	m_skinModel->SetToonRender();

	//スキンモデルの座標を設定。
	m_skinModel->SetPosition(m_position);

	//スキンモデルの回転を設定。
	m_skinModel->SetRotation(m_rotation);
}

void JumpFloor::CreateStaticObject()
{
	//静的オブジェクトを作成。
	m_static.CreateMeshObject(m_skinModel->GetSkinModel(), m_position, m_rotation);
}
