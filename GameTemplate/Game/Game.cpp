#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "Stage2.h"
#include "GameCamera.h"
#include "Title.h"
#include "PlayerHP.h"
#include "GameOver.h"
#include "Saru.h"
#include "Enemy.h"
#include "GunEnemy.h"
#include "JumpFloor.h"
#include "Wall.h"
#include "level/Level.h"
#include "ButtonUI.h"
#include "Sky.h"
#include "SaruCounter.h"
#include "EnemyCounter.h"

EStage Game::stageNo = eStage_1;

const int STAGE2_DOWN_ENEMY_NO = 10;		//ステージ２の敵を倒す数。
const int GAMECLEAR_TIME = 90;				//ゲームクリアまでのタイム。
const int GAMEOVER_TITLE_TIME = 90;			//ゲームオーバーからタイトルに遷移するまでのタイム。
const float PLAYER_DEATH_HEIGHT = -300.0f;	//プレイヤーが落ちた時にゲームオーバーになる高さ。
Game::Game()
{
	std::wstring tklFileName;
	if (stageNo == eStage_1) {
		tklFileName = L"Assets/level/Stage_01.tkl";
		m_gameBGM.Init(L"Assets/Sound/GameBgm.wav");
		m_gameBGM.Play(true);
	}
	else if (stageNo == eStage_2) {
		tklFileName = L"Assets/level/Stage_02.tkl";
		m_gameBGM2.Init(L"Assets/Sound/GameBgm2.wav");
		m_gameBGM2.Play(true);
	}
	//ステージを構築
	
	
	std::vector< LevelObjectData> pathObjData;		//パスのデータを保存する。
	//レベルを初期化
	m_level.Init(tklFileName.c_str(), [&](const LevelObjectData& objData)
	{
		if (wcscmp(objData.name, L"stage_01") == 0) {
			m_stage = NewGO<Stage>();
			m_stage->SetPosition(objData.position);
			m_stage->SetRotation(objData.rotation);
			return true;
		}
		else if (wcscmp(objData.name, L"stage_02") == 0) {
			m_stage2 = NewGO<Stage2>();
			m_stage2->SetPosition(objData.position);
			m_stage2->SetRotation(objData.rotation);
			return true;
		}
		else if (wcscmp(objData.name, L"SkyBox") == 0) {
			m_sky = NewGO<Sky>();
			m_sky->SetPosition(objData.position);
			m_sky->SetRotation(objData.rotation);
			return true;
		}

		else if (wcscmp(objData.name, L"wall") == 0) {
			m_wall = NewGO<Wall>();
			m_wall->SetPosition(objData.position);
			m_wall->SetRotation(objData.rotation);
			m_wall->CreateStaticObject();
			return true;
		}

		else if (wcscmp(objData.name, L"Player") == 0) {
			m_pl = NewGO<Player>();
			m_pl->Setposition(objData.position);
			m_pl->SetRotation(objData.rotation);
			return true;
		}

		else if (wcsncmp(objData.name, L"Saru", 4) == 0) {
			Saru* saru = NewGO<Saru>();
			//5文字目以降にサルの番号が入っている。
			std::wstring saruNoStr = &objData.name[5];
			int saruNo = stoi(saruNoStr);
			m_sarus[saruNo] = saru;

			saru->SetPos(objData.position);
			saru->SetRotation(objData.rotation);
			saru->SetPlayer(m_pl);
			m_pl->SetSaru(saru);
			m_saruNo++;
			return true;
		}

		else if (wcscmp(objData.name, L"Enemy") == 0) {
			Enemy* enemy = NewGO<Enemy>();
			m_enemys.push_back(enemy);
			enemy->SetPosition(objData.position);
			enemy->SetRotation(objData.rotation);
			enemy->SetPlayer(m_pl);
			m_pl->SetEnemy(enemy);
			m_downEnemyNo++;
			return true;
		}
		else if (wcscmp(objData.name, L"GunEnemy") == 0) {
			GunEnemy* gunEnemy = NewGO<GunEnemy>();
			m_gunEnemys.push_back(gunEnemy);
			gunEnemy->SetPosition(objData.position);
			gunEnemy->SetRotation(objData.rotation);
			gunEnemy->SetPlayer(m_pl);
			m_pl->SetGunEnemy(gunEnemy);
			return true;
		}
		else if (wcscmp(objData.name, L"JumpFloor") == 0) {
			m_jumpFloor = NewGO<JumpFloor>();
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


	m_gCamera = NewGO<GameCamera>();
	m_gCamera->SetPlayer(m_pl);
}

Game::~Game()
{
	DeleteGO(m_stage);
	DeleteGO(m_stage2);
	DeleteGO(m_jumpFloor);
	DeleteGO(m_wall);
	DeleteGO(m_sky);

	DeleteGO(m_pl);

	for( int i = 0; i < m_saruNo; i++){
		DeleteGO(m_sarus[i]);
	}

	for (auto& enemy : m_enemys) {
		DeleteGO(enemy);
	}

	for (auto& gunEnemy : m_gunEnemys) {
		DeleteGO(gunEnemy);
	}

	DeleteGO(m_playerHP);
	DeleteGO(m_gCamera);
	DeleteGO(m_buttonUI);
	DeleteGO(m_saruCounter);
	DeleteGO(m_enemyCounter);

	//プレイヤーのHPがなくなったらタイトルに遷移する。
	if (m_playerHP->GetGameOver() == true) {
		NewGO<Title>();
	}
	//ステージ番号がeStage_1の時にステージ2に遷移する。
	else if (stageNo == eStage_1) {
		stageNo = eStage_2;
		NewGO<Game>();
	}
	//ステージ番号がeStage_2の時にタイトルに遷移する。
	else if (stageNo == eStage_2) {
		NewGO<Title>();
		stageNo = eStage_1;
	}
}

bool Game::Start()
{
	m_playerHP = NewGO<PlayerHP>();
	m_buttonUI = NewGO<ButtonUI>();
	m_saruCounter = NewGO<SaruCounter>();
	m_enemyCounter = NewGO<EnemyCounter>();
	
	m_pl->SetPlayerHP(m_playerHP);

	//サルの数をフォントで表示。
	m_saruCounter->SetSaruNumber(m_saruNo);

	//エネミーの数をフォントで表示。
	if (stageNo == eStage_1) {
		//ステージ１の倒すエネミーの数
		m_enemyCounter->SetEnemyNumber(m_downEnemyNo);
	}
	else if (stageNo == eStage_2) {
		//ステージ２の倒すエネミーの数
		m_enemyCounter->SetEnemyNumber(STAGE2_DOWN_ENEMY_NO);
	}
	return true;
}



void Game::Update()
{
	if (g_pad[0].IsTrigger(enButtonSelect) == true) {
		DeleteGO(this);
	}

	if (stageNo == eStage_1) {
		m_stage->SetSaruNo(m_saruNo);
		m_stage->SetSaruCounter(m_pl->GetSaruCount());
		m_stage->SetDownEnemyNo(m_downEnemyNo);
		m_stage->SetDownEnemyCounter(m_pl->GetEnemyCount());
		//ステージ１のゲームクリア
		if (m_stage->GetClearTimer() == GAMECLEAR_TIME)
		{
			DeleteGO(this);
		}
		//ステージ１のゲームオーバー
		else if (m_playerHP->GetGameOver() == true)
		{
			m_stage->SetGameOverFlag(m_playerHP->GetGameOver());
			m_pl->StateDeath();
			if (m_stage->GetOverTimer() == GAMEOVER_TITLE_TIME)
			{
				DeleteGO(this);
			}
		}
	}
	
	else if (stageNo == eStage_2) {
		m_stage2->SetSaruNo(m_saruNo);
		m_stage2->SetSaruCounter(m_pl->GetSaruCount());
		m_stage2->SetDownEnemyNo(STAGE2_DOWN_ENEMY_NO);
		m_stage2->SetDownEnemyCounter(m_pl->GetEnemyCount());
		//ステージ２のゲームクリア
		if (m_stage2->GetClearTimer() == GAMECLEAR_TIME)
		{
			DeleteGO(this);
		}
		//ステージ１のゲームオーバー
		else if (m_playerHP->GetGameOver() == true)
		{
			m_stage2->SetGameOverFlag(m_playerHP->GetGameOver());
			m_pl->StateDeath();
			if (m_stage2->GetOverTimer() == GAMEOVER_TITLE_TIME)
			{
				DeleteGO(this);
			}
		}
	}

	//捕まえたサルの数をフォントで表示。
	m_saruCounter->AddSaruCounter(m_pl->GetSaruCount());

	if (m_downEnemyNo >= m_pl->GetEnemyCount()) {
		//ステージ１の倒したエネミーの数をフォントで表示。
		m_enemyCounter->AddEnemyCounter(m_pl->GetEnemyCount());
	}
	else if (STAGE2_DOWN_ENEMY_NO >= m_pl->GetEnemyCount()) {
		//ステージ２の倒したエネミーの数をフォントで表示。
		m_enemyCounter->AddEnemyCounter(m_pl->GetEnemyCount());
	}
}

void Game::Draw()
{
	//レベルを描画
	m_level.Draw();
}