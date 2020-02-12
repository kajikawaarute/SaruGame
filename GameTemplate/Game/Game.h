#pragma once
#include "IGameObject.h"
#include "Sprite.h"
#include "RenderTarget.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Player;
class Stage;
class Enemy;
class GameCamera;
class Saru;
class BananaPeel;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
	/// <summary>
	/// Effekserの初期化
	/// </summary>
	void InitEffekseer();
private:
	CSoundEngine m_soundEnigne;					//サウンドエンジン
	CSoundSource m_gameBGM;						//ゲームのBGM

	//Effekseerマネージャー管理
	Effekseer::Manager* m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_effekt = nullptr;		//エフェクト
	Effekseer::Handle m_playEffectHandle = -1;
	Player* m_pl = nullptr;						//プレイヤーのインスタンス
	Stage* m_stage = nullptr;					//ステージのインスタンス
	Enemy* m_ene = nullptr;						//エネミーのインスタンス
	GameCamera* m_gCamera = nullptr;			//ゲームカメラのインスタンス
	Saru* m_saru[2] = {nullptr, nullptr};		//サルクラスのインスタンス
	BananaPeel* m_banana = nullptr;				//バナナの皮のインスタンス
};

