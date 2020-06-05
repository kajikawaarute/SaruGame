#pragma once
#include "IGameObject.h"
#include "physics/PhysicsStaticObject.h"
#include "level/Level.h"
#include "Saru.h"

class Saru;
class Player;
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	void Update();
	void Draw();
private:
	Level level;		//レベルのインスタンス
	Player* m_player = nullptr;
	std::vector< Saru* > m_sarus;
};

