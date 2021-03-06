#pragma once
#include "IPlayerState.h"

class PlayerStateSliped : public IPlayerState
{
public:
	/// <summary>
	/// 滑っている状態に遷移したときに呼ばれる関数
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 滑っている状態を抜ける時に呼ばれる関数
	/// </summary>
	void OnLeave();
};

