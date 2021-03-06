#pragma once
#include "ISaruState.h"

class SaruStateRun : public ISaruState
{
public:
	/// <summary>
	/// 走り状態に遷移したときに呼ばれる関数
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 走り状態を抜ける時に呼ばれる関数
	/// </summary>
	void OnLeave();

};

