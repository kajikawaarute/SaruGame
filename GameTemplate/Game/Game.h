#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "level/Level.h"

class Player;
class Stage;
class Enemy;
class GameCamera;
class Saru;
class Title;
class PlayerHP;
class GameClear;
class JumpFloor;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
private:
	prefab::CSoundSource m_gameBGM;									//ゲームのBGM

	Player* m_pl = nullptr;																//プレイヤーのインスタンス
	//Stage* m_stage = nullptr;															//ステージのインスタンス
	Enemy* m_enemy[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};		//エネミーのインスタンス
	GameCamera* m_gCamera = nullptr;													//ゲームカメラのインスタンス
	Saru* m_saru[3] = { nullptr, nullptr , nullptr};									//サルクラスのインスタンス
	PlayerHP* m_playerHP = nullptr;														//プレイヤーHPのインスタンス
	GameClear* m_gameClear = nullptr;													//ゲームクリアのインスタンス
	JumpFloor* m_jumpFloor = nullptr;													//ジャンプ床のインスタンス

	std::vector<Saru*> m_sarus;								//サルのリスト
	std::vector<Enemy*> m_enemys;							//エネミーのリスト

	Level level;
};

