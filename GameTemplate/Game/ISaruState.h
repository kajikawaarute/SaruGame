#pragma once

class Saru;

class ISaruState
{
public:
	ISaruState()
	{
	}
	~ISaruState()
	{
	}

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="saru"></param>
	void Init(Saru* saru)
	{
		m_saru = saru;
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
	Saru* m_saru = nullptr;
};

