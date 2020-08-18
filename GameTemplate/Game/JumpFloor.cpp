#include "stdafx.h"
#include "JumpFloor.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "graphics/ToonRender.h"

const float FLOOR_JUMP_POWER = 4000.0f;		//ジャンプ台ジャンプパワー。
JumpFloor::JumpFloor()
{
	m_model.Init(L"Assets/modelData/JumpFloor2.cmo");

	//アニメーションをロード
	m_animationClip[enAnim_wait].Load(L"Assets/animData/JumpFloor-wait.tka");
	m_animationClip[enAnim_jump].Load(L"Assets/animData/JumpFloor-jump.tka");

	//初期アニメーションを設定
	m_enAnimClip = enAnim_wait;

	//アニメーションを初期化
	m_animation.Init(m_model, m_animationClip, enAnim_num);

	m_ghost.CreateBox(m_position, m_rotation,{450.0f, 60.0f, 400.0f});

	//シャドウレシーバーを設定
	m_model.SetShadowReciever(true);
}


JumpFloor::~JumpFloor()
{
	m_ghost.Release();
}

void JumpFloor::Update()
{
	g_physics.ContactTest(m_player->GetcharaCon(), [&](const btCollisionObject& contactObject) {
		if (m_ghost.IsSelf(contactObject)) {
			m_player->GetMoveSpd().y = FLOOR_JUMP_POWER;
			m_enAnimClip = enAnim_jump;
		}
		});

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

	m_animation.Update(1.0f / 30.0f);

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//トゥーンレンダを設定。
	ToonRender::GetInstance().RegistToonRender(&m_model);
}

void JumpFloor::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void JumpFloor::CreateStaticObject()
{
	m_static.CreateMeshObject(m_model, m_position, m_rotation);
}
