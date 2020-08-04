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
	RenderTarget m_depthBuffer;		//�[�x�l���o�͂���p�̃o�b�t�@
};

