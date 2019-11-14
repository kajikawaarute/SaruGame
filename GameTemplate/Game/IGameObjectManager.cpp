#include "stdafx.h"
#include "IGameObjectManager.h"

//IGameObjectManagerクラスのインスタンス。
IGameObjectManager g_goMgr;

void IGameObjectManager::Update()
{
	//登録されているゲームオブジェクトの更新処理を呼ぶ。
	for (auto go : m_goList) {
		go->Update();
	}
	for (auto go : m_goList) {
		go->Draw();
	}

	//すべてのゲームオブジェクトの
	for (auto it = m_goList.begin(); it != m_goList.end();) {
		if ((*it)->IsRequestDelete()) {
			//削除リクエストを受けているので削除。
			delete* it;
			it = m_goList.erase(it);
		}
		else {
			//リクエストを受けていない。
			it++;
		}
	}

}

