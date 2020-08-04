#include "stdafx.h"
#include "ToonRender.h"


ToonRender::ToonRender()
{
	//深度値出力用のレンダリングターゲットを作成。
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
