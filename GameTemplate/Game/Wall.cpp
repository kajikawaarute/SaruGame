#include "stdafx.h"
#include "Wall.h"

Wall::Wall()
{
	//���f���̏������B
	m_skinModel = NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/wall.cmo");

	//�V���h�E���V�[�o�[��ݒ�B
	m_skinModel->SetShadowReciever();
}


Wall::~Wall()
{
	//�X�L�����f�����폜�B
	DeleteGO(m_skinModel);
}

void Wall::Update()
{
	//�g�D�[�������_��ݒ�B
	m_skinModel->SetToonRender();

	//�X�L�����f���̍��W��ݒ�B
	m_skinModel->SetPosition(m_position);

	//�X�L�����f���̉�]��ݒ�B
	m_skinModel->SetRotation(m_rotation);
}

void Wall::CreateStaticObject()
{
	//�ÓI�I�u�W�F�N�g���쐬�B
	m_static.CreateMeshObject(m_skinModel->GetSkinModel(), m_position, m_rotation);
}
