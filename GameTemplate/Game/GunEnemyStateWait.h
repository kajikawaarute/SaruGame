#pragma once
#include "IGunEnemyState.h"

class GunEnemyStateWait : public IGunEnemyState
{
public:
	/// <summary>
	/// �ҋ@��ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐��B
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �ҋ@��Ԃ̍X�V�֐��B
	/// </summary>
	void Update();

	/// <summary>
	/// �ҋ@��Ԃ𔲂��鎞�ɌĂ΂��֐��B
	/// </summary>
	void OnLeave();
};

