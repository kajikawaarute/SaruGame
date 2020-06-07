#pragma once
#include "IGameObject.h"
#include "physics/PhysicsStaticObject.h"
#include "level/Level.h"

class Saru;
class Player;
class Enemy;
class JumpFloor;
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	void Update();
	void Draw();

	Player* GetPlayer()
	{
		return m_pl;
	}
private:
	Level m_level;

	Player* m_pl = nullptr;																//プレイヤーのインスタンス
	Enemy* m_enemy[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };		//エネミーのインスタンス
	Saru* m_saru[3] = { nullptr, nullptr , nullptr };									//サルクラスのインスタンス
	JumpFloor* m_jumpFloor = nullptr;													//ジャンプ床のインスタンス

	std::vector<Saru*> m_sarus;								//サルのリスト
	std::vector<Enemy*> m_enemys;							//エネミーのリスト
};

