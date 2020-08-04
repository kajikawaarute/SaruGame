#pragma once
#include "IGameObject.h"
#include "RenderTarget.h"

class ToonRender
{
public:
	ToonRender();
	~ToonRender();
	void Update();
	void Draw();
private:
	RenderTarget m_depthBuffer;		//深度値を出力する用のバッファ
};

