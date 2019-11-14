#include "stdafx.h"
#include "Stage.h"
#include "level/Level.h"

Stage::Stage()
{
	//レベルを初期化
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
	//レベルを描画
	level.Draw();
}