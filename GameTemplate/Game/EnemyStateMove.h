#pragma once
#include "IEnenyState.h"

//エネミーの移動状態
class EnemyStateMove : public IEnenyState
{
public:
	/// <summary>
	/// 移動状態に遷移したときに呼ばれる関数。
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 移動状態の更新関数。
	/// </summary>
	void Update();

	/// <summary>
	/// 移動状態を抜ける時に呼ばれる関数。
	/// </summary>
	void OnLeave();

};

