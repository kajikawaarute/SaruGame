#include "stdafx.h"
#include "Sky.h"

Sky::Sky()
{
	//���f���̏������B
	m_skinModel = g_goMgr.NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/SkyBox.cmo");
}

Sky::~Sky()
{
	//�X�L�����f�����폜�B
	g_goMgr.DeleteGO(m_skinModel);
}

void Sky::Update()
{
	//�X�L�����f���̍��W��ݒ�B
	m_skinModel->SetPosition(m_position);

	//�X�L�����f���̉�]��ݒ�B
	m_skinModel->SetRotation(m_rotation);
}
