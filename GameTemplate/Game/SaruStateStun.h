#pragma once
#include "ISaruState.h"

class SaruStateStun : public ISaruState
{
public:
	/// <summary>
	/// 怯み状態に遷移したときに呼ばれる関数
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 怯み状態を抜ける時に呼ばれる関数
	/// </summary>
	void OnLeave();

};

