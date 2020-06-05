#include "stdafx.h"
#include "Stage.h"
#include "level/Level.h"
#include "IGameObjectManager.h"
#include "Saru.h"
#include "Player.h"

Stage::Stage()
{
	//ƒŒƒxƒ‹‚ğ‰Šú‰»
	//level.Init(L"Assets/level/Stage_01.tkl", [&](const LevelObjectData& objData)
	//	{
	//		/*if (wcscmp(objData.name, L"Player") == 0) {
	//			auto player = g_goMgr.NewGO<Player>();
	//			player->Setposition(objData.position);
	//			return true;
	//		}*/

	//		/*if (wcscmp(objData.name, L"Assets/modelData/Saru.cmo") == 0) {
	//			auto saru = g_goMgr.NewGO<Saru>();
	//			m_sarus.push_back(saru);
	//			return true;
	//		}*/
	//		return false;
	//	});
}


Stage::~Stage()
{
}

void Stage::Update()
{
	for (auto saru : m_sarus) {
		saru->Update();
		saru->Draw();
	}
}

void Stage::Draw()
{
	//ƒŒƒxƒ‹‚ğ•`‰æ
	level.Draw();
}