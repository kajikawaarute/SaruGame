#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Player;
class Stage;
class GameCamera;
class Title;
class PlayerHP;
class GameClear;
class GameOver;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
private:
	prefab::CSoundSource m_gameBGM;				//ゲームのBGM

	Player* m_pl = nullptr;						//プレイヤーのインスタンス
	Stage* m_stage = nullptr;					//ステージのインスタンス
	GameCamera* m_gCamera = nullptr;			//ゲームカメラのインスタンス
	PlayerHP* m_playerHP = nullptr;				//プレイヤーHPのインスタンス
	GameClear* m_gameClear = nullptr;			//ゲームクリアのインスタンス
	GameOver* m_gameOver = nullptr;				//ゲームオーバーのインスタンス

	int m_gameClearTimer = 0;					//ゲームクリアまでのタイマー
};

