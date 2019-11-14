#include "stdafx.h"
#include "Stage.h"
#include "level/Level.h"

Stage::Stage()
{
	//ƒŒƒxƒ‹‚ğ‰Šú‰»
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
	//ƒŒƒxƒ‹‚ğ•`‰æ
	level.Draw();
}