#pragma once
#include "IPlayerState.h"

class PlayerStateJump : public IPlayerState
{
public:
	/// <summary>
	/// �W�����v��ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐�
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �W�����v��Ԃ𔲂��鎞�ɌĂ΂��֐�
	/// </summary>
	void OnLeave();
};

