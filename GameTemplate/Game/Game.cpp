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
#include "GunEnemy.h"
#include "JumpFloor.h"
#include "Wall.h"
#include "level/Level.h"
#include "ButtonUI.h"
#include "Sky.h"

int Game::stageNo = 0;
Game::Game()
{
	m_gameBGM.Init(L"Assets/Sound/GameBgm.wav");
	m_gameBGM.Play(true);

	stageNo = 1;

	//ステージ1
	if (stageNo == 0) {
		std::vector< LevelObjectData> pathObjData;		//パスのデータを保存する。
		//レベルを初期化
		m_level.Init(L"Assets/level/Stage_01.tkl", [&](const LevelObjectData& objData)
			{
				if (wcscmp(objData.name, L"stage_01") == 0) {
					m_stage = g_goMgr.NewGO<Stage>();
					m_stage->Setposition(objData.position);
					m_stage->SetRotation(objData.rotation);
					return true;
				}

				else if (wcscmp(objData.name, L"SkyBox") == 0) {
					m_sky = g_goMgr.NewGO<Sky>();
					m_sky->SetPosition(objData.position);
					m_sky->SetRotation(objData.rotation);
					return true;
				}

				else if (wcscmp(objData.name, L"wall") == 0) {
					m_wall = g_goMgr.NewGO<Wall>();
					m_wall->SetPosition(objData.position);
					m_wall->SetRotation(objData.rotation);
					m_wall->CreateStaticObject();
					return true;
				}

				else if (wcscmp(objData.name, L"Player") == 0) {
					m_pl = g_goMgr.NewGO<Player>();
					m_pl->Setposition(objData.position);
					m_pl->SetRotation(objData.rotation);
					return true;
				}

				else if (wcsncmp(objData.name, L"Saru", 4) == 0) {
					Saru* saru = g_goMgr.NewGO<Saru>();
					//5文字目以降にサルの番号が入っている。
					std::wstring saruNoStr = &objData.name[5];
					int saruNo = stoi(saruNoStr);
					m_sarus[saruNo] = saru;

					saru->SetPos(objData.position);
					saru->SetRotation(objData.rotation);
					saru->SetPlayer(m_pl);
					m_pl->SetSaru(saru);
					m_saruNo = 3;
					return true;
				}

				else if (wcscmp(objData.name, L"Enemy") == 0) {
					Enemy* enemy = g_goMgr.NewGO<Enemy>();
					m_enemys.push_back(enemy);
					enemy->SetPosition(objData.position);
					enemy->SetRotation(objData.rotation);
					enemy->SetPlayer(m_pl);
					m_pl->SetEnemy(enemy);
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
				else if ((wcsncmp(objData.name, L"Path", 4) == 0)) {
					//パスデータはいったん保存しておく。
					pathObjData.push_back(objData);
					return true;
				}
			
				return false;
			});
			//保存したパスデータを使って、サルにパスを設定していく。
			for (const LevelObjectData& objData : pathObjData) {
				//objData.nameを解析して、該当するサルの番号を調べる。
				std::wstring saruNoStr = &objData.nameWStr[5];
				int saruNo = stoi(saruNoStr);
				//調べた番号のサルにパスを設定する。
				m_sarus[saruNo]->PushPathPosition(objData.position);
			}
	}
	//ステージ2
	if (stageNo == 1){
		std::vector< LevelObjectData> pathObjData;		//パスのデータを保存する。
		m_level.Init(L"Assets/level/Stage_02.tkl", [&](const LevelObjectData& objData)
			{
				if (wcscmp(objData.name, L"stage_02") == 0) {
					m_stage2 = g_goMgr.NewGO<Stage2>();
					m_stage2->Setposition(objData.position);
					m_stage2->SetRotation(objData.rotation);
					return true;
				}

				else if (wcscmp(objData.name, L"SkyBox") == 0) {
					m_sky = g_goMgr.NewGO<Sky>();
					m_sky->SetPosition(objData.position);
					m_sky->SetRotation(objData.rotation);
					return true;
				}

				else if (wcscmp(objData.name, L"Player") == 0) {
					m_pl = g_goMgr.NewGO<Player>();
					m_pl->Setposition(objData.position);
					m_pl->SetRotation(objData.rotation);
					return true;
				}

				else if (wcsncmp(objData.name, L"Saru", 4) == 0) {
					Saru* saru = g_goMgr.NewGO<Saru>();
					//5文字目以降にサルの番号が入っている。
					std::wstring saruNoStr = &objData.name[5];
					int saruNo = stoi(saruNoStr);

					m_sarus[saruNo] = saru;
					saru->SetPos(objData.position);
					saru->SetRotation(objData.rotation);
					saru->SetPlayer(m_pl);
					m_pl->SetSaru(saru);
					m_saruNo = 1;
					return true;
				}

				else if (wcscmp(objData.name, L"Enemy") == 0) {
					Enemy* enemy = g_goMgr.NewGO<Enemy>();
					m_enemys.push_back(enemy);
					enemy->SetPosition(objData.position);
					enemy->SetRotation(objData.rotation);
					enemy->SetPlayer(m_pl);
					m_pl->SetEnemy(enemy);
					return true;
				}

				else if (wcscmp(objData.name, L"GunEnemy") == 0) {
					GunEnemy* gunEnemy = g_goMgr.NewGO<GunEnemy>();
					m_gunEnemys.push_back(gunEnemy);
					gunEnemy->SetPosition(objData.position);
					gunEnemy->SetRotation(objData.rotation);
					gunEnemy->SetPlayer(m_pl);
					m_pl->SetGunEnemy(gunEnemy);
					return true;
				}

				else if ((wcsncmp(objData.name, L"Path", 4) == 0)) {
					//パスデータはいったん保存しておく。
					pathObjData.push_back(objData);
					return true;
				}

				return false;
			});
		//保存したパスデータを使って、サルにパスを設定していく。
		for (const LevelObjectData& objData : pathObjData) {
			//objData.nameを解析して、該当するサルの番号を調べる。
			std::wstring saruNoStr = &objData.nameWStr[5];
			int saruNo = stoi(saruNoStr);
			//調べた番号のサルにパスを設定する。
			m_sarus[saruNo]->PushPathPosition(objData.position);
		}
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
	g_goMgr.DeleteGO(m_wall);
	g_goMgr.DeleteGO(m_sky);

	g_goMgr.DeleteGO(m_pl);

	for( int i = 0; i < m_saruNo; i++){
		g_goMgr.DeleteGO(m_sarus[i]);
	}

	for (auto& enemy : m_enemys) {
		g_goMgr.DeleteGO(enemy);
	}

	g_goMgr.DeleteGO(m_playerHP);
	g_goMgr.DeleteGO(m_gCamera);
	g_goMgr.DeleteGO(m_gameClear);
	g_goMgr.DeleteGO(m_gameOver);
	g_goMgr.DeleteGO(m_buttonUI);

	//プレイヤーのHPがなくなったらタイトルに遷移する。
	if (m_playerHP->GetGameOver() == true) {
		g_goMgr.NewGO<Title>();
	}
	//ステージ番号が0の時にタイトルに遷移する。
	else if (stageNo == 0) {
		/*stageNo = 1;
		g_goMgr.NewGO<Game>();*/
		g_goMgr.NewGO<Title>();
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
	if (m_pl->GetSaruCount() == m_saruNo)
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
	if (m_playerHP->GetGameOver() == true || m_pl->GetPos().y < -300.0f) {
		m_gameOverTimer++;
		if (m_gameOverTimer == 10) {
			m_gameOver = g_goMgr.NewGO<GameOver>();
			m_pl->StateDeath();
		}
		if (m_gameOverTimer == 60) {
			g_goMgr.DeleteGO(this);
		}
	}
}

void Game::Draw()
{
	//レベルを描画
	m_level.Draw();
}