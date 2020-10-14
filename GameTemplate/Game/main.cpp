#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "Title.h"
#include "sound/SoundEngine.h"

Effekseer::Manager* g_effekseerManager = nullptr;
EffekseerRenderer::Renderer* g_effekseerRenderer = nullptr;

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//Titleクラスのインスタンス
	Title* title = NewGO<Title>();

	//サウンドエンジンのインスタンス
	CSoundEngine soundEngine;
	//サウンドエンジンの初期化
	soundEngine.Init();

	//Effekseerマネージャー管理
	//レンダラーを初期化。
	g_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		GetD3DDeviceGraphicsEngine(),			//D3Dデバイス。
		GetD3DDeviceContextGraphicsEngine(),	//D3Dデバイスコンテキスト。
		20000									//板ポリの最大数。
	);
	//エフェクトマネージャを初期化。
	g_effekseerManager = Effekseer::Manager::Create(10000);

	// 描画用インスタンスから描画機能を設定
	g_effekseerManager->SetSpriteRenderer(g_effekseerRenderer->CreateSpriteRenderer());
	g_effekseerManager->SetRibbonRenderer(g_effekseerRenderer->CreateRibbonRenderer());
	g_effekseerManager->SetRingRenderer(g_effekseerRenderer->CreateRingRenderer());
	g_effekseerManager->SetTrackRenderer(g_effekseerRenderer->CreateTrackRenderer());
	g_effekseerManager->SetModelRenderer(g_effekseerRenderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	g_effekseerManager->SetTextureLoader(g_effekseerRenderer->CreateTextureLoader());
	g_effekseerManager->SetModelLoader(g_effekseerRenderer->CreateModelLoader());

	CStopwatch sw;
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//1フレームの時間計測を開始。
		sw.Start();
		//描画開始。
		GraphicsEngine::GetInstance()->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		//ゲームオブジェクトマネージャーの更新
		IGameObjectManager::GetInstance()->Update();

		g_effekseerRenderer->BeginRendering();
		g_effekseerManager->Draw();
		g_effekseerRenderer->EndRendering();

		//Effekseerを更新
		g_effekseerManager->Update();

		//Effekseerカメラ行列を設定。
		//まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//カメラ行列とプロジェクション行列を設定。
		g_effekseerRenderer->SetCameraMatrix(efCameraMat);
		g_effekseerRenderer->SetProjectionMatrix(efProjMat);

		//カメラの更新。
		g_camera3D.Update();
		//サウンドエンジンの更新
		soundEngine.Update();
		//描画終了。
		GraphicsEngine::GetInstance()->EndRender();
		//1フレームの時間計測を終了。
		sw.Stop();
		//経過時間を記憶しておく。
		GameTime().PushFrameDeltaTime(sw.GetElapsed());
	}
}