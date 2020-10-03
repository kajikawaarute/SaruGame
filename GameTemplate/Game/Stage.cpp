#include "stdafx.h"
#include "Stage.h"
#include "IGameObjectManager.h"


Stage::Stage()
{
	//���f���̏������B
	m_skinModel = g_goMgr.NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/stage_01.cmo");

	//�ÓI�I�u�W�F�N�g���쐬�B
	m_static.CreateMeshObject(m_skinModel->GetSkinModel(), m_position, m_rotation);

	//�V���h�E���V�[�o�[��ݒ�
	m_skinModel->SetShadowReciever();
}


Stage::~Stage()
{
	//�X�L�����f�����폜�B
	g_goMgr.DeleteGO(m_skinModel);
}

void Stage::Update()
{
	//�V���h�E�L���X�^�[��ݒ�
	m_skinModel->SetShadowCaster();

	//�g�D�[�������_��ݒ�B
	m_skinModel->SetToonRender();

	//�X�L�����f���̍��W��ݒ�B
	m_skinModel->SetPosition(m_position);

	//�X�L�����f���̉�]��ݒ�B
	m_skinModel->SetRotation(m_rotation);
}