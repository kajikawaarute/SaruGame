#pragma once
#include "IEnenyState.h"

//エネミーの攻撃状態
class EnemyStateAttack : public IEnenyState
{
public:
	/// <summary>
	/// 攻撃状態に遷移したときに呼ばれる関数。
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 攻撃状態の更新関数。
	/// </summary>
	void Update();

	/// <summary>
	/// 攻撃状態を抜ける時に呼ばれる関数。
	/// </summary>
	void OnLeave();

};

