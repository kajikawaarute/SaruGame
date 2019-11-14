#pragma once
#include "IGameObject.h"
#include "physics/PhysicsStaticObject.h"
#include "level/Level.h"
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	void Update();
	void Draw();
private:
	Level level;		//レベルのインスタンス
};

