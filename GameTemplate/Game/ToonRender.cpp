#include "stdafx.h"
#include "ToonRender.h"


ToonRender::ToonRender()
{
	//�[�x�l�o�͗p�̃����_�����O�^�[�Q�b�g���쐬�B
	m_depthBuffer.Create(2048, 2048, DXGI_FORMAT_R32_FLOAT);
}


ToonRender::~ToonRender()
{
}

void ToonRender::Update()
{
}

void ToonRender::Draw()
{
}
