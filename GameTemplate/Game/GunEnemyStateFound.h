#pragma once
#include "IGunEnemyState.h"

class GunEnemyStateFound : public IGunEnemyState
{
public:
	/// <summary>
	/// ����������ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐��B
	/// </summary>
	void OnEnter();

	/// <summary>
	/// ����������Ԃ̍X�V�֐��B
	/// </summary>
	void Update();

	/// <summary>
	/// ����������Ԃ𔲂��鎞�ɌĂ΂��֐��B
	/// </summary>
	void OnLeave();
};

