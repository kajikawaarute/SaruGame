#include "stdafx.h"
#include "JumpFloor.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "graphics/ToonRender.h"

const float FLOOR_JUMP_POWER = 4000.0f;		//�W�����v��W�����v�p���[�B
JumpFloor::JumpFloor()
{
	m_model.Init(L"Assets/modelData/JumpFloor2.cmo");

	//�A�j���[�V���������[�h
	m_animationClip[enAnim_wait].Load(L"Assets/animData/JumpFloor-wait.tka");
	m_animationClip[enAnim_jump].Load(L"Assets/animData/JumpFloor-jump.tka");

	//�����A�j���[�V������ݒ�
	m_enAnimClip = enAnim_wait;

	//�A�j���[�V������������
	m_animation.Init(m_model, m_animationClip, enAnim_num);

	m_ghost.CreateBox(m_position, m_rotation,{450.0f, 60.0f, 400.0f});

	//�V���h�E���V�[�o�[��ݒ�
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

	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//�g�D�[�������_��ݒ�B
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
