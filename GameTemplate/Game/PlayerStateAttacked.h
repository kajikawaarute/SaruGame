#pragma once
#include "IPlayerState.h"

class PlayerStateAttacked : public IPlayerState
{
public:
	/// <summary>
	/// �U�����ꂽ��ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐�
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �U�����ꂽ��Ԃ𔲂��鎞�ɌĂ΂��֐�
	/// </summary>
	void OnLeave();
};

