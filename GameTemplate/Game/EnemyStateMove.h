#pragma once
#include "IEnenyState.h"

//�G�l�~�[�̈ړ����
class EnemyStateMove : public IEnenyState
{
public:
	/// <summary>
	/// �ړ���ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐��B
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �ړ���Ԃ̍X�V�֐��B
	/// </summary>
	void Update();

	/// <summary>
	/// �ړ���Ԃ𔲂��鎞�ɌĂ΂��֐��B
	/// </summary>
	void OnLeave();

};

