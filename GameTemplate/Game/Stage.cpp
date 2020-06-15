#include "stdafx.h"
#include "Stage.h"
#include "level/Level.h"
#include "IGameObjectManager.h"
#include "Player.h"
#include "Saru.h"
#include "Enemy.h"
#include "JumpFloor.h"

Stage::Stage()
{
	//レベルを初期化
	m_level.Init(L"Assets/level/Stage_01.tkl", [&](const LevelObjectData& objData)
		{
			if (wcscmp(objData.name, L"Player") == 0) {
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
			return false;
		});
}


Stage::~Stage()
{
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
}

void Stage::Update()
{
}

void Stage::Draw()
{
	//レベルを描画
	m_level.Draw();
}