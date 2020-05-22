#pragma once
#include "ISaruState.h"

class SaruStateWait : public ISaruState
{
public:
	/// <summary>
	/// 待機状態に遷移したときに呼ばれる関数
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 待機状態を抜ける時に呼ばれる関数
	/// </summary>
	void OnLeave();

};

