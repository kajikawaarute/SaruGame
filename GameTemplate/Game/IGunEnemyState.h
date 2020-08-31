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
	/// �������B
	/// </summary>
	/// <param name="gunEnemy"></param>
	void Init(GunEnemy* gunEnemy)
	{
		m_gunEnemy = gunEnemy;
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
	GunEnemy* m_gunEnemy = nullptr;	//���̏�Ԃ�ێ����Ă���K���G�l�~�[�B
};

