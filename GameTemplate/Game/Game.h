#pragma once
#include "IGameObject.h"


class Player;
class Stage;
class Enemy;
class GameCamera;
class GetAmi;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
private:
	Player* m_pl = nullptr;		//プレイヤーのインスタンス
	Stage* m_stage = nullptr;		//ステージのインスタンス
	Enemy* m_ene = nullptr;		//エネミーのインスタンス
	GameCamera* m_gCamera = nullptr; //ゲームカメラのインスタンス
	
};

