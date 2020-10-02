#include "stdafx.h"
#include "IGameObjectManager.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"

//IGameObjectManagerクラスのインスタンス。
IGameObjectManager g_goMgr;

void IGameObjectManager::Update()
{

	//登録されているゲームオブジェクトのスタート関数を呼ぶ。
	for (auto go : m_goList) {
		//スタート関数を呼んでいなかったら呼ぶ。
		if (!go->GetisStart()) {
			go->Start();
			go->SetStart(true);
		}
	}
	int i = 0;
	//登録されているゲームオブジェクトの更新処理を呼ぶ。
	for (auto go : m_goList) {
		//スタート関数が呼ばれた更新関数を呼ぶ。
		if (go->GetisStart()) {
			go->Update();
		}
		i++;
	}

	//シャドウマップ
	ShadowMap::GetInstance().Draw();

	//トゥーンレンダー
	ToonRender::GetInstance().Draw();

	//登録されているゲームオブジェクトの描画処理を呼ぶ。
	for (auto go : m_goList) {
		//スタート関数が呼ばれた描画関数を呼ぶ。
		if(go->GetisStart()) {
			go->Draw();
		}
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

