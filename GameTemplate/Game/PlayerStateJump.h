#pragma once
#include "IPlayerState.h"

class PlayerStateJump : public IPlayerState
{
public:
	/// <summary>
	/// ジャンプ状態に遷移したときに呼ばれる関数
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// ジャンプ状態を抜ける時に呼ばれる関数
	/// </summary>
	void OnLeave();
};

