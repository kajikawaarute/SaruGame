#pragma once
#include "ISaruState.h"

class SaruStateGet : public ISaruState
{
public:
	/// <summary>
	/// �ߊl��ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐�
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �ߊl��Ԃ𔲂��鎞�ɌĂ΂��֐�
	/// </summary>
	void OnLeave();

};

