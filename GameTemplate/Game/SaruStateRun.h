#pragma once
#include "ISaruState.h"

class SaruStateRun : public ISaruState
{
public:
	/// <summary>
	/// �����ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐�
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �����Ԃ𔲂��鎞�ɌĂ΂��֐�
	/// </summary>
	void OnLeave();
};

