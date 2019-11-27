#pragma once
#include "IGameObject.h"
#include "Sprite.h"
#include "RenderTarget.h"

class Player;
class Stage;
class Enemy;
class GameCamera;
class Saru;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
private:
	Player* m_pl = nullptr;						//プレイヤーのインスタンス
	Stage* m_stage = nullptr;					//ステージのインスタンス
	Enemy* m_ene = nullptr;						//エネミーのインスタンス
	GameCamera* m_gCamera = nullptr;			//ゲームカメラのインスタンス
	Saru* m_saru = nullptr;						//サルクラスのインスタンス
	RenderTarget m_mainRenderTarget;			//メインレンダリングターゲット
	Sprite m_copyMainRtToFrameBufferSprite;		//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
};

