#pragma once
#include "IPlayerState.h"

class PlayerStateSliped : public IPlayerState
{
public:
	/// <summary>
	/// �����Ă����ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐�
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �����Ă����Ԃ𔲂��鎞�ɌĂ΂��֐�
	/// </summary>
	void OnLeave();
};

