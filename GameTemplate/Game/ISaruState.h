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
	/// ������
	/// </summary>
	/// <param name="saru"></param>
	void Init(Saru* saru)
	{
		m_saru = saru;
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
	Saru* m_saru = nullptr;
};

