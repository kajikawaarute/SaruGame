#pragma once
#include "IPlayerState.h"

class PlayerStateDeath : public IPlayerState
{
public:
	/// <summary>
	/// 死亡状態に遷移したときに呼ばれる関数
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 死亡状態を抜ける時に呼ばれる関数
	/// </summary>
	void OnLeave();
};

