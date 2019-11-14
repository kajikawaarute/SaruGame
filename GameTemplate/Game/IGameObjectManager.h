#pragma once
#include "IGameObject.h"
class IGameObjectManager
{
public:
	/// <summary>
	/// 更新。
	/// </summary>
	void Update();
	/// <summary>
	/// ゲームオブジェクトを追加。
	/// </summary>
	template <class T>
	T* NewGO()
	{
		T* newObj = new T;
		m_goList.push_back(newObj);
		return newObj;
	}

	void DeleteGO(IGameObject* go)
	{
		//リストから検索して、見つかったら削除する。
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			if ((*it) == go) {
				go->RequestDelete();
			}
		}
	}
private:
	//IGameObject*の可変長配列を
	//メンバ変数に追加する。
	std::vector<IGameObject*> m_goList;		//ゲームオブジェクトのリスト
};

//外部からアクセスするので、extern宣言も必要。
extern IGameObjectManager g_goMgr;