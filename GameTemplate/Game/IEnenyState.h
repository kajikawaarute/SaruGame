#pragma once

class Enemy;
//エネミーの状態のインターフェースクラス。
class IEnenyState
{
public:
	IEnenyState()
	{
	}
	virtual ~IEnenyState() 
	{
	}
	
	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="enemy"></param>
	void Init(Enemy* enemy)
	{
		m_enemy = enemy;
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
	Enemy* m_enemy = nullptr;	//この状態を保持しているエネミー。
};

