#pragma once
class EnemyCounter : public IGameObject
{
public:
	EnemyCounter();
	~EnemyCounter();

	/// <summary>
	/// エネミ－カウンターのUpdate関数前に呼ばれる更新関数。
	/// </summary>
	/// <returns>trueを返すと一度だけ呼ばれる</returns>
	bool Start();

	/// <summary>
	/// エネミーカウンターの更新関数。
	/// </summary>
	void Update();

	/// <summary>
	/// エネミーカウンターの描画関数。
	/// </summary>
	void Draw();

	/// <summary>
	/// 倒したエネミ－の数をカウントする。
	/// </summary>
	/// <param name="eneCounter">倒したエネミ－の数</param>
	void AddEnemyCounter(const int &eneCounter)
	{
		m_enemyCounter = eneCounter;
	}

	/// <summary>
	/// エネミーの数を設定。
	/// </summary>
	/// <param name="eneNo">エネミーの数</param>
	void SetEnemyNumber(const int &eneNo)
	{
		m_enemyCount = eneNo;
	}
private:
	FontRender* m_fontRender = nullptr;				//フォントのインスタンス

	CVector2 m_fontPosition = { 20.0f, 150.0f };	//フォントの座標
	CVector2 m_fontScale = { 0.7f, 0.7f };			//フォントの拡大率

	int m_enemyCount = 0;		//エネミ－の数
	int m_enemyCounter = 0;		//倒したエネミ－の数

	wchar_t m_text[64];			//テキスト
};

