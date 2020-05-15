#pragma once
#include "IEnenyState.h"

//エネミーの待機状態
class EnemyStateWait : public IEnenyState
{
public:
	/// <summary>
	/// 待機状態に遷移したときに呼ばれる関数。
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 待機状態の更新関数。
	/// </summary>
	void Update();

	/// <summary>
	/// 待機状態を抜ける時に呼ばれる関数。
	/// </summary>
	void OnLeave();
};

