#pragma once
#include "IPlayerState.h"

class PlayerStateWait : public IPlayerState
{
public:
	/// <summary>
	/// �ҋ@��ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐�
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �ҋ@��Ԃ𔲂��鎞�ɌĂ΂��֐�
	/// </summary>
	void OnLeave();
};

