#pragma once

class Enemy;
//�G�l�~�[�̏�Ԃ̃C���^�[�t�F�[�X�N���X�B
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
	/// �������B
	/// </summary>
	/// <param name="enemy"></param>
	void Init(Enemy* enemy)
	{
		m_enemy = enemy;
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
	Enemy* m_enemy = nullptr;	//���̏�Ԃ�ێ����Ă���G�l�~�[�B
};

