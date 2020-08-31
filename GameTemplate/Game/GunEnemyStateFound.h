#pragma once
#include "IGunEnemyState.h"

class GunEnemyStateFound : public IGunEnemyState
{
public:
	/// <summary>
	/// 見つかった状態に遷移したときに呼ばれる関数。
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 見つかった状態の更新関数。
	/// </summary>
	void Update();

	/// <summary>
	/// 見つかった状態を抜ける時に呼ばれる関数。
	/// </summary>
	void OnLeave();
};

