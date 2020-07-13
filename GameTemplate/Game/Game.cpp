#include "stdafx.h"
#include "IGameObjectManager.h"
#include "Game.h"
#include "Stage.h"
#include "Stage2.h"
#include "GameCamera.h"
#include "Title.h"
#include "PlayerHP.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Saru.h"
#include "Enemy.h"
#include "JumpFloor.h"
#include "level/Level.h"
#include "ButtonUI.h"

int Game::stageNo = 0;
Game::Game()
{
	m_gameBGM.Init(L"Assets/Sound/GameBgm.wav");
	m_gameBGM.Play(true);

	//stageNo = 1;

	if (stageNo == 0) {
		//レベルを初期化
		m_level.Init(L"Assets/level/Stage_01.tkl", [&](const LevelObjectData& objData)
			{
				if (wcscmp(objData.name, L"stage_01") == 0) {
					m_stage = g_goMgr.NewGO<Stage>();
					m_stage->Setposition(objData.position);
					m_stage->SetRotation(objData.rotation);
					return true;
				}

				else if (wcscmp(objData.name, L"Player") == 0) {
					m_pl = g_goMgr.NewGO<Player>();
					m_pl->Setposition(objData.position);
					m_pl->SetRotation(objData.rotation);
					return true;
				}

				else if (wcscmp(objData.name, L"Saru_1") == 0) {
					m_saru[0] = g_goMgr.NewGO<Saru>();
					m_sarus.push_back(m_saru[0]);
					m_saru[0]->SetPos(objData.position);
					m_saru[0]->SetRotation(objData.rotation);
					m_saru[0]->SetPlayer(m_pl);
					m_pl->SetSaru(m_saru[0]);
					return true;
				}

				else if (wcscmp(objData.name, L"Saru_2") == 0) {
					m_saru[1] = g_goMgr.NewGO<Saru>();
					m_sarus.push_back(m_saru[1]);
					m_saru[1]->SetPos(objData.position);
					m_saru[1]->SetRotation(objData.rotation);
					m_saru[1]->SetPlayer(m_pl);
					m_pl->SetSaru(m_saru[1]);
					return true;
				}

				else if (wcscmp(objData.name, L"Saru_3") == 0) {
					m_saru[2] = g_goMgr.NewGO<Saru>();
					m_sarus.push_back(m_saru[2]);
					m_saru[2]->SetPos(objData.position);
					m_saru[2]->SetRotation(objData.rotation);
					m_saru[2]->SetPlayer(m_pl);
					m_pl->SetSaru(m_saru[2]);
					return true;
				}

				else if (wcscmp(objData.name, L"Enemy_1") == 0) {
					m_enemy[0] = g_goMgr.NewGO<Enemy>();
					m_enemys.push_back(m_enemy[0]);
					m_enemy[0]->SetPosition(objData.position);
					m_enemy[0]->SetRotation(objData.rotation);
					m_enemy[0]->SetPlayer(m_pl);
					m_pl->SetEnemy(m_enemy[0]);
					return true;
				}

				else if (wcscmp(objData.name, L"Enemy_2") == 0) {
					m_enemy[1] = g_goMgr.NewGO<Enemy>();
					m_enemys.push_back(m_enemy[1]);
					m_enemy[1]->SetPosition(objData.position);
					m_enemy[1]->SetRotation(objData.rotation);
					m_enemy[1]->SetPlayer(m_pl);
					m_pl->SetEnemy(m_enemy[1]);
					return true;
				}

				else if (wcscmp(objData.name, L"Enemy_3") == 0) {
					m_enemy[2] = g_goMgr.NewGO<Enemy>();
					m_enemys.push_back(m_enemy[2]);
					m_enemy[2]->SetPosition(objData.position);
					m_enemy[2]->SetRotation(objData.rotation);
					m_enemy[2]->SetPlayer(m_pl);
					m_pl->SetEnemy(m_enemy[2]);
					return true;
				}

				else if (wcscmp(objData.name, L"Enemy_4") == 0) {
					m_enemy[3] = g_goMgr.NewGO<Enemy>();
					m_enemys.push_back(m_enemy[3]);
					m_enemy[3]->SetPosition(objData.position);
					m_enemy[3]->SetRotation(objData.rotation);
					m_enemy[3]->SetPlayer(m_pl);
					m_pl->SetEnemy(m_enemy[3]);
					return true;
				}

				else if (wcscmp(objData.name, L"Enemy_5") == 0) {
					m_enemy[4] = g_goMgr.NewGO<Enemy>();
					m_enemys.push_back(m_enemy[4]);
					m_enemy[4]->SetPosition(objData.position);
					m_enemy[4]->SetRotation(objData.rotation);
					m_enemy[4]->SetPlayer(m_pl);
					m_pl->SetEnemy(m_enemy[4]);
					return true;
				}

				else if (wcscmp(objData.name, L"Enemy_6") == 0) {
					m_enemy[5] = g_goMgr.NewGO<Enemy>();
					m_enemys.push_back(m_enemy[5]);
					m_enemy[5]->SetPosition(objData.position);
					m_enemy[5]->SetRotation(objData.rotation);
					m_enemy[5]->SetPlayer(m_pl);
					m_pl->SetEnemy(m_enemy[5]);
					return true;
				}

				else if (wcscmp(objData.name, L"JumpFloor") == 0) {
					m_jumpFloor = g_goMgr.NewGO<JumpFloor>();
					m_jumpFloor->SetPosition(objData.position);
					m_jumpFloor->SetPositonGhost(objData.position);
					m_jumpFloor->CreateStaticObject();
					m_jumpFloor->SetPlayer(m_pl);
					return true;
				}
				else if ((wcscmp(objData.name, L"Path_1") == 0)) {
					m_saru[0]->PushPathPosition(objData.position);
					return true;
				}
				else if ((wcscmp(objData.name, L"Path_2") == 0)) {
					m_saru[0]->PushPathPosition(objData.position);
					return true;
				}
				else if ((wcscmp(objData.name, L"Path_3") == 0)) {
					m_saru[0]->PushPathPosition(objData.position);
					return true;
				}
				else if ((wcscmp(objData.name, L"Path_4") == 0)) {
					m_saru[0]->PushPathPosition(objData.position);
					return true;
				}
				else if ((wcscmp(objData.name, L"Path_5") == 0)) {
					m_saru[1]->PushPathPosition(objData.position);
					return true;
				}
				else if ((wcscmp(objData.name, L"Path_6") == 0)) {
					m_saru[1]->PushPathPosition(objData.position);
					return true;
				}
				else if ((wcscmp(objData.name, L"Path_7") == 0)) {
					m_saru[1]->PushPathPosition(objData.position);
					return true;
				}
				else if ((wcscmp(objData.name, L"Path_8") == 0)) {
					m_saru[2]->PushPathPosition(objData.position);
					return true;
				}
				else if ((wcscmp(objData.name, L"Path_9") == 0)) {
					m_saru[2]->PushPathPosition(objData.position);
					return true;
				}
				else if ((wcscmp(objData.name, L"Path_10") == 0)) {
					m_saru[2]->PushPathPosition(objData.position);
					return true;
				}
				return false;
			});
	}
	//↓ステージ２を入れる
	if (stageNo == 1)
	{
		m_level.Init(L"Assets/level/Stage_02.tkl", [&](const LevelObjectData& objData)
			{
				if (wcscmp(objData.name, L"stage_02") == 0) {
					m_stage2 = g_goMgr.NewGO<Stage2>();
					m_stage2->Setposition(objData.position);
					m_stage2->SetRotation(objData.rotation);
					return true;
				}

				else if (wcscmp(objData.name, L"Player") == 0) {
					m_pl = g_goMgr.NewGO<Player>();
					m_pl->Setposition(objData.position);
					m_pl->SetRotation(objData.rotation);
					return true;
				}
				return false;
			});
	}
	m_gCamera = g_goMgr.NewGO<GameCamera>();
	m_gCamera->SetPlayer(m_pl);

	m_playerHP = g_goMgr.NewGO<PlayerHP>();
	m_pl->SetPlayerHP(m_playerHP);

	m_buttonUI = g_goMgr.NewGO<ButtonUI>();
}


Game::~Game()
{
	g_goMgr.DeleteGO(m_stage);
	g_goMgr.DeleteGO(m_stage2);
	g_goMgr.DeleteGO(m_jumpFloor);

	g_goMgr.DeleteGO(m_pl);

	g_goMgr.DeleteGO(m_saru[0]);
	g_goMgr.DeleteGO(m_saru[1]);
	g_goMgr.DeleteGO(m_saru[2]);

	g_goMgr.DeleteGO(m_enemy[0]);
	g_goMgr.DeleteGO(m_enemy[1]);
	g_goMgr.DeleteGO(m_enemy[2]);
	g_goMgr.DeleteGO(m_enemy[3]);
	g_goMgr.DeleteGO(m_enemy[4]);
	g_goMgr.DeleteGO(m_enemy[5]);

	g_goMgr.DeleteGO(m_playerHP);
	g_goMgr.DeleteGO(m_gCamera);
	g_goMgr.DeleteGO(m_gameClear);
	g_goMgr.DeleteGO(m_gameOver);
	g_goMgr.DeleteGO(m_buttonUI);

	//プレイヤーのHPがなくなったらタイトルに遷移する。
	if (m_playerHP->GetGameOver() == true) {
		g_goMgr.NewGO<Title>();
	}
	//ステージ番号が0の時にステージ2に遷移する。
	else if (stageNo == 0) {
		stageNo = 1;
		g_goMgr.NewGO<Game>();
	}
	//ステージ番号が1の時にタイトルに遷移する。
	else if (stageNo == 1) {
		g_goMgr.NewGO<Title>();
		stageNo = 0;
	}
}



void Game::Update()
{
	//セレクトボタンを押すとタイトル画面に遷移
	if (g_pad[0].IsTrigger(enButtonSelect)) {
		g_goMgr.DeleteGO(this);
	}

	//サルを全員捕まえたらゲームクリア
	if (m_pl->GetSaruCount() == 3)
	{
		m_gameClearTimer++;
		if (m_gameClearTimer == 30) {
			m_gameClear = g_goMgr.NewGO<GameClear>();
		}
		if (m_gameClearTimer == 120) {
			g_goMgr.DeleteGO(this);
		}
	}

	//プレイヤーのHPがなくなったらゲームオーバー
	if (m_playerHP->GetGameOver() == true) {
		m_gameOverTimer++;
		if (m_gameOverTimer == 50) {
			m_gameOver = g_goMgr.NewGO<GameOver>();
			m_pl->StateDeath();
		}
		if (m_gameOverTimer == 150) {
			g_goMgr.DeleteGO(this);
		}
	}
}

void Game::Draw()
{
	//レベルを描画
	m_level.Draw();
}