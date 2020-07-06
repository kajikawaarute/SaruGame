#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "level/Level.h"

class Player;
class Saru;
class Player;
class Enemy;
class JumpFloor;

class Stage;
class GameCamera;
class Title;
class PlayerHP;
class GameClear;
class GameOver;
class Game : public IGameObject
{
public:
	static int stageNo;	//ステージ番号
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

	Enemy* m_enemy[6] = { nullptr };		//エネミーのインスタンス
	Saru* m_saru[3] = { nullptr };			//サルクラスのインスタンス
	JumpFloor* m_jumpFloor = nullptr;		//ジャンプ床のインスタンス

	std::vector<Saru*> m_sarus;				//サルのリスト
	std::vector<Enemy*> m_enemys;			//エネミーのリスト

	Level m_level;

	int m_gameClearTimer = 0;					//ゲームクリアまでのタイマー
};

