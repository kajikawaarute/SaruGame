#pragma once
#include "IGameObject.h"
#include "FontRender.h"

class SaruCounter : public IGameObject
{
public:
	SaruCounter();
	~SaruCounter();

	/// <summary>
	/// サルカウンターのUpdate関数前に呼ばれる開始関数。
	/// </summary>
	/// <returns>trueを返すと一度だけ呼ばれる</returns>
	bool Start();

	/// <summary>
	/// サルカウンターの更新関数。
	/// </summary>
	void Update();

	/// <summary>
	/// サルカウンターの描画関数。
	/// </summary>
	void Draw();

	/// <summary>
	/// 捕まえたサルをカウントする。
	/// </summary>
	/// <param name="saruCount">捕まえたサルの数</param>
	/// <returns>捕まえたサルの数</returns>
	int AddSaruCounter(int saruCount)
	{
		m_saruCounter = saruCount;
		return m_saruCounter;
	}

	/// <summary>
	/// サルの数を設定。
	/// </summary>
	/// <param name="saruNo">サルの数</param>
	/// <returns>サルの数</returns>
	int SetSaruNumber(int saruNo)
	{
		m_saruCount = saruNo;
		return m_saruCount;
	}

private:
	FontRender* m_fontRender = nullptr;				//フォントのインスタンス

	CVector2 m_fontPosition = { 20.0f, 100.0f };	//フォントの座標

	int m_saruCount = 0;		//サルの数
	int m_saruCounter = 0;		//捕まえたサルの数

	wchar_t m_text[64];			//テキスト
};

