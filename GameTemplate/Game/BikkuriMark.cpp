#include "stdafx.h"
#include "BikkuriMark.h"

BikkuriMark::BikkuriMark()
{
	//���f���̏������B
	m_skinModel = g_goMgr.NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/Bikkuri_Mark.cmo");
}


BikkuriMark::~BikkuriMark()
{
	//�X�L�����f�����폜�B
	g_goMgr.DeleteGO(m_skinModel);
}

void BikkuriMark::Update()
{
	//�g�D�[�������_�[��ݒ�B
	m_skinModel->SetToonRender();

	//�X�L�����f���̍��W��ݒ�B
	m_skinModel->SetPosition(m_position);

	//�X�L�����f���̉�]��ݒ�B
	m_skinModel->SetRotation(m_rotation);
}