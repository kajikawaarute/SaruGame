#include "stdafx.h"
#include "Stage.h"
#include "level/Level.h"

Stage::Stage()
{
	//���x����������
	level.Init(L"Assets/level/Stage_01.tkl", nullptr);
}


Stage::~Stage()
{
}

void Stage::Update()
{
	
}

void Stage::Draw()
{
	//���x����`��
	level.Draw();
}