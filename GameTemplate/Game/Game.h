#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "DirectXTK/Inc/SpriteBatch.h"

class Player;
class Stage;
class Enemy;
class GameCamera;
class Saru;
class Title;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
private:
	CSoundEngine m_soundEnigne;					//サウンドエンジン
	prefab::CSoundSource m_gameBGM;				//ゲームのBGM

	Player* m_pl = nullptr;						//プレイヤーのインスタンス
	Stage* m_stage = nullptr;					//ステージのインスタンス
	Enemy* m_ene[2] = { nullptr, nullptr};						//エネミーのインスタンス
	GameCamera* m_gCamera = nullptr;			//ゲームカメラのインスタンス
	Saru* m_saru[2] = {nullptr, nullptr};		//サルクラスのインスタンス
};

