#include "stdafx.h"
#include "Stage.h"
#include "level/Level.h"
#include "IGameObjectManager.h"
#include "Player.h"
#include "Saru.h"
#include "Enemy.h"
#include "JumpFloor.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"

Stage::Stage()
{
	//���f���̏������B
	m_model.Init(L"Assets/modelData/stage_01.cmo");

	//�ÓI�I�u�W�F�N�g���쐬�B
	m_static.CreateMeshObject(m_model, m_position, m_rotation);

	//�V���h�E���V�[�o�[��ݒ�
	m_model.SetShadowReciever(true);
}


Stage::~Stage()
{
}

void Stage::Update()
{
	//�V���h�E�L���X�^�[��ݒ�
	ShadowMap::GetInstance().RegistShadowCaster(&m_model);

	//�g�D�[�������_��ݒ�B
	ToonRender::GetInstance().RegistToonRender(&m_model);

	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Stage::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}