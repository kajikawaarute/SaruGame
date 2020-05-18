#pragma once
#include "ISaruState.h"

class SaruStateGet : public ISaruState
{
public:
	/// <summary>
	/// 捕獲状態に遷移したときに呼ばれる関数
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 捕獲状態を抜ける時に呼ばれる関数
	/// </summary>
	void OnLeave();
};

