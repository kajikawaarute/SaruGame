#pragma once
#include "IPlayerState.h"

class PlayerStateMove : public IPlayerState
{
public:
	/// <summary>
	/// �ړ���ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐�
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �ړ���Ԃ𔲂��鎞�ɌĂ΂��֐�
	/// </summary>
	void OnLeave();
};

