#pragma once
#include "ISaruState.h"

class SaruStateStun : public ISaruState
{
public:
	/// <summary>
	/// ���ݏ�ԂɑJ�ڂ����Ƃ��ɌĂ΂��֐�
	/// </summary>
	void OnEnter();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// ���ݏ�Ԃ𔲂��鎞�ɌĂ΂��֐�
	/// </summary>
	void OnLeave();

};

