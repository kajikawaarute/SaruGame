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
	/// ������
	/// </summary>
	/// <param name="player"></param>
	void Init(Player* player)
	{
		m_player = player;
	}

	/// <summary>
	/// ��ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐��B
	/// </summary>
	virtual void OnEnter() = 0;

	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// ��Ԃ𔲂��鎞�ɌĂ΂��֐��B
	/// </summary>
	virtual void OnLeave() = 0;

protected:
	Player* m_player = nullptr;
};

