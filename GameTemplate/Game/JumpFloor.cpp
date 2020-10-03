#include "stdafx.h"
#include "JumpFloor.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

const float FLOOR_JUMP_POWER = 4000.0f;		//�W�����v��W�����v�p���[�B
JumpFloor::JumpFloor()
{
	//���f���̏������B
	m_skinModel = g_goMgr.NewGO <SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/JumpFloor2.cmo");

	//�A�j���[�V���������[�h
	m_animationClip[enAnim_wait].Load(L"Assets/animData/JumpFloor-wait.tka");
	m_animationClip[enAnim_jump].Load(L"Assets/animData/JumpFloor-jump.tka");

	//�����A�j���[�V������ݒ�
	m_enAnimClip = enAnim_wait;

	//�A�j���[�V������������
	m_animation.Init(m_skinModel->GetSkinModel(), m_animationClip, enAnim_num);

	//�S�[�X�g�I�u�W�F�N�g�𐶐��B
	m_ghost.CreateBox(m_position, m_rotation, m_ghostObjectScale);

	//�V���h�E���V�[�o�[��ݒ�B
	m_skinModel->SetShadowReciever();
}


JumpFloor::~JumpFloor()
{
	//�X�L�����f�����폜�B
	g_goMgr.DeleteGO(m_skinModel);
}

void JumpFloor::Update()
{
	//�S�[�X�g�I�u�W�F�N�g�̔���B
	g_physics.ContactTest(m_player->GetcharaCon(), [&](const btCollisionObject& contactObject) {
		if (m_ghost.IsSelf(contactObject)) {
			prefab::CSoundSource* jumpFloorSE = g_goMgr.NewGO<prefab::CSoundSource>();
			jumpFloorSE->Init(L"Assets/Sound/JumpFloorSE.wav");
			jumpFloorSE->Play(false);
			m_player->GetMoveSpd().y = FLOOR_JUMP_POWER;
			m_enAnimClip = enAnim_jump;
		}
		});

	//�W�����v��̃A�j���[�V����
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

	//�A�j���[�V�����̍X�V�B
	m_animation.Update(1.0f / 30.0f);

	//�g�D�[�������_��ݒ�B
	m_skinModel->SetToonRender();

	//�X�L�����f���̍��W��ݒ�B
	m_skinModel->SetPosition(m_position);

	//�X�L�����f���̉�]��ݒ�B
	m_skinModel->SetRotation(m_rotation);
}

void JumpFloor::CreateStaticObject()
{
	//�ÓI�I�u�W�F�N�g���쐬�B
	m_static.CreateMeshObject(m_skinModel->GetSkinModel(), m_position, m_rotation);
}
