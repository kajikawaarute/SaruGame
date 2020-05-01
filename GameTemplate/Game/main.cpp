#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "IGameObjectManager.h"
#include "Title.h"
#include "sound/SoundEngine.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//Titleクラスのインスタンス
	Title* title = g_goMgr.NewGO<Title>();

	//サウンドエンジンのインスタンス
	CSoundEngine soundEngine;
	//サウンドエンジンの初期化
	soundEngine.Init();

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		//ゲームオブジェクトマネージャーの更新
		g_goMgr.Update();
		//カメラの更新。
		g_camera3D.Update();
		//サウンドエンジンの更新
		soundEngine.Update();
		//描画終了。
		g_graphicsEngine->EndRender();
	}
}