#pragma once

class Player;

class IPlayerState
{
public:
	IPlayerState() 
	{
	}
	~IPlayerState()
	{
	}

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="player"></param>
	void Init(Player* player)
	{
		m_player = player;
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
	Player* m_player = nullptr;
};

