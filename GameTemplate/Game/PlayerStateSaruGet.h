#pragma once
#include "IPlayerState.h"

class Player;
class PlayerStateSaruGet : public IPlayerState
{
public:
	/// <summary>
	/// サルの捕獲状態に遷移したときに呼ばれる関数
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// サルに捕獲状態を抜ける時に呼ばれる関数
	/// </summary>
	void OnLeave();
};

