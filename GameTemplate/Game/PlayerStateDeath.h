#pragma once
#include "IPlayerState.h"

class PlayerStateDeath : public IPlayerState
{
public:
	/// <summary>
	/// ���S��ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐�
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// ���S��Ԃ𔲂��鎞�ɌĂ΂��֐�
	/// </summary>
	void OnLeave();
};

