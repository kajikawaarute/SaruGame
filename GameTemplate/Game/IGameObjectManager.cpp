#include "stdafx.h"
#include "IGameObjectManager.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"

//IGameObjectManagerクラスのインスタンス。
IGameObjectManager g_goMgr;

void IGameObjectManager::Update()
{
	for (auto go : m_goList) {
		go->Start();
	}
	int i = 0;
	//登録されているゲームオブジェクトの更新処理を呼ぶ。
	for (auto go : m_goList) {
		go->Update();
		i++;
	}

	//シャドウマップ
	ShadowMap::GetInstance().Draw();

	//トゥーンレンダー
	ToonRender::GetInstance().Draw();

	for (auto go : m_goList) {
		go->Draw();
	}

	//すべてのゲームオブジェクトのリストの検索
	for (auto it = m_goList.begin(); it != m_goList.end();) {
		if ((*it)->IsRequestDelete()) {
			//削除リクエストを受けているので削除。
			delete* it;
			it = m_goList.erase(it);
			//it++;
		}
		else {
			//リクエストを受けていない。
			it++;
		}
	}

}

