#include "stdafx.h"
#include "Stage2.h"
#include "IGameObjectManager.h"

Stage2::Stage2()
{
	//���f���̏������B
	m_skinModel = g_goMgr.NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/stage_02.cmo");

	//�ÓI�I�u�W�F�N�g���쐬�B
	m_staticObject.CreateMeshObject(m_skinModel->GetSkinModel(), m_position, m_rotation);

	//�V���h�E���V�[�o�[��ݒ�B
	m_skinModel->SetShadowReciever();
}

Stage2::~Stage2()
{
	//�X�L�����f�����폜�B
	g_goMgr.DeleteGO(m_skinModel);
}

void Stage2::Update()
{
	//�V���h�E�L���X�^�[��ݒ�B
	m_skinModel->SetShadowCaster();

	//�g�D�[�������_�[��ݒ�B
	m_skinModel->SetToonRender();

	//�X�L�����f���̍��W��ݒ�B
	m_skinModel->SetPosition(m_position);

	//�X�L�����f���̉�]��ݒ�B
	m_skinModel->SetRotation(m_rotation);
}