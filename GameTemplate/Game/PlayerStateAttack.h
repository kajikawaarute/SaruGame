#pragma once
#include "IPlayerState.h"

class PlayerStateAttack : public IPlayerState
{
public:
	/// <summary>
	/// 攻撃状態に遷移したときに呼ばれる関数
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 攻撃状態を抜ける時に呼ばれる関数
	/// </summary>
	void OnLeave();
};

