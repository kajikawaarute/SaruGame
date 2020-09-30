#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "level/Level.h"


class Player;
class Saru;
class Enemy;
class GunEnemy;
class JumpFloor;
class Wall;
class Sky;

class Stage;
class Stage2;
class GameCamera;
class Title;
class PlayerHP;
class GameClear;
class GameOver;
class ButtonUI;
class FontRender;
class Game : public IGameObject
{
public:
	static int stageNo;	//ステージ番号
	Game();
	~Game();

	/// <summary>
	/// ゲームの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// ゲームの描画関数
	/// </summary>
	void Draw();
private:
	enum { MAX_SARU = 100 };				//1ステージのサルの最大数。
	prefab::CSoundSource m_gameBGM;			//ステージ1のBGM
	prefab::CSoundSource m_gameBGM2;		//ステージ2のBGM

	Player* m_pl = nullptr;					//プレイヤーのインスタンス

	Stage* m_stage = nullptr;				//ステージのインスタンス
	Stage2* m_stage2 = nullptr;				//ステージ2のインスタンス
	JumpFloor* m_jumpFloor = nullptr;		//ジャンプ床のインスタンス
	Wall* m_wall = nullptr;					//ステージ壁のインスタンス
	Sky* m_sky = nullptr;					//空のインスタンス

	GameCamera* m_gCamera = nullptr;		//ゲームカメラのインスタンス

	PlayerHP* m_playerHP = nullptr;			//プレイヤーHPのインスタンス
	GameClear* m_gameClear = nullptr;		//ゲームクリアのインスタンス
	GameOver* m_gameOver = nullptr;			//ゲームオーバーのインスタンス
	ButtonUI* m_buttonUI = nullptr;			//ボタンUIのインスタンス
	

	int m_saruNo = 0;						//サルの数
	Saru* m_sarus[MAX_SARU] = {nullptr};	//サルのリスト
	std::vector<Enemy*> m_enemys;			//エネミーのリスト
	std::vector<GunEnemy*> m_gunEnemys;		//ガンエネミーのリスト

	Level m_level;		//レベルのインスタンス

	int m_gameClearTimer = 0;		//ゲームクリアまでのタイマー
	int m_gameOverTimer = 0;		//ゲームオーバーまでのタイマー

	FontRender* m_font = nullptr;

	CVector2 m_FontPosition = { 100.0f, 100.0f };	//フォントの座標
	CVector4 m_FontColor = CVector4::White();		//フォントのカラー
	CVector2 m_FontScale = CVector2::One();			//フォントのサイズ
	CVector2 m_FontPivot = CVector2::Zero();		//フォントのピボット
	float m_FontRotation = 0.0f;					//フォントの回転
};

