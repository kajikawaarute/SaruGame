#pragma once
#include "IEnenyState.h"

//�G�l�~�[�̍U�����
class EnemyStateAttack : public IEnenyState
{
public:
	/// <summary>
	/// �U����ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐��B
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �U����Ԃ̍X�V�֐��B
	/// </summary>
	void Update();

	/// <summary>
	/// �U����Ԃ𔲂��鎞�ɌĂ΂��֐��B
	/// </summary>
	void OnLeave();

};

