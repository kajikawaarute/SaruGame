#pragma once
#include "IPlayerState.h"

class PlayerStateAttacked : public IPlayerState
{
public:
	/// <summary>
	/// 攻撃された状態に遷移したときに呼ばれる関数
	/// </summary>
	void OnEnter();

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 攻撃された状態を抜ける時に呼ばれる関数
	/// </summary>
	void OnLeave();
private:
	float m_timer = 0.0f;	//タイマー(単位:秒)
};

