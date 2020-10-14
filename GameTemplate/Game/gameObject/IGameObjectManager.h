#pragma once
#include "IGameObject.h"
class IGameObjectManager
{
	private:
	//コンストラクタとデストラクタをprivateに宣言して、
	//外部からインスタンスを作成できないようにする。
	IGameObjectManager() {}
	~IGameObjectManager() {}
public:
	/// <summary>
	/// IGameObjectManagerのインスタンスを取得する。
	/// </summary>
	/// <returns>IGameObjectManagerのインスタンス</returns>
	static IGameObjectManager* GetInstance()
	{
		static IGameObjectManager* instance = nullptr;
		if (instance == nullptr) {
			instance = new IGameObjectManager();
		}
		return instance;
	}
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

	/// <summary>
	/// ゲームオブジェクトを削除。
	/// </summary>
	/// <param name="go">削除するゲームオブジェクト</param>
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
	/*/// <summary>
	/// IGameObjectManagerのインスタンスを作成する。
	/// </summary>
	static void CreateInstance()
	{
		if (m_instance != nullptr) {
			//IGameObjectManagerのインスタンスは複数作れない！！！
			//おそらくプログラムの間違いなのでプログラムを停止させる。
			std::abort();
		}
		m_instance = new IGameObjectManager;
	}*/

	/*/// <summary>
	/// IGameObjectManagerのインスタンスを破棄する。
	/// </summary>
	static void DeleteInstance()
	{
		//delete m_instance;
		//m_instance = nullptr;
	}*/
private:
	//IGameObject*の可変長配列を
	//メンバ変数に追加する。
	std::list<IGameObject*> m_goList;		//ゲームオブジェクトのリスト
	//static const IGameObjectManager* m_instance;	//唯一のインスタンス。
};

//ヘルパー関数
/// <summary>
/// ゲームオブジェクトを追加。
/// </summary>
template <class T>
static inline T* NewGO()
{
	return IGameObjectManager::GetInstance()->NewGO<T>();
}

/// <summary>
/// ゲームオブジェクトを削除。
/// </summary>
/// <param name="go">削除するゲームオブジェクト</param>
static inline void DeleteGO(IGameObject* go)
{
	IGameObjectManager::GetInstance()->DeleteGO(go);
}