#pragma once
#include "IPlayerState.h"

class PlayerStateAttack : public IPlayerState
{
public:
	/// <summary>
	/// �U����ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐�
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �U����Ԃ𔲂��鎞�ɌĂ΂��֐�
	/// </summary>
	void OnLeave();
};

