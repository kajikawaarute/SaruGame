#pragma once
#include "ISaruState.h"

class SaruStateWait : public ISaruState
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

