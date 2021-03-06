#pragma once
#include "IPlayerState.h"

class PlayerStateMove : public IPlayerState
{
public:
	/// <summary>
	/// 移動状態に遷移したときに呼ばれる関数
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 移動状態を抜ける時に呼ばれる関数
	/// </summary>
	void OnLeave();
};

