#pragma once

class GunEnemy;
class IGunEnemyState
{
public:
	IGunEnemyState()
	{
	}
	virtual ~IGunEnemyState()
	{
	}

	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="gunEnemy"></param>
	void Init(GunEnemy* gunEnemy)
	{
		m_gunEnemy = gunEnemy;
	}

	/// <summary>
	/// 状態に遷移したときに呼ばれる関数。
	/// </summary>
	virtual void OnEnter() = 0;

	/// <summary>
	/// 更新関数。
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 状態を抜ける時に呼ばれる関数。
	/// </summary>
	virtual void OnLeave() = 0;
protected:
	GunEnemy* m_gunEnemy = nullptr;	//この状態を保持しているガンエネミー。
};

