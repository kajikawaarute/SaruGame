#pragma once
#include "IPlayerState.h"

class Player;
class PlayerStateSaruGet : public IPlayerState
{
public:
	/// <summary>
	/// �T���̕ߊl��ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐�
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �T���ɕߊl��Ԃ𔲂��鎞�ɌĂ΂��֐�
	/// </summary>
	void OnLeave();
};

