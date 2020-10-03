#pragma once
#include "IGameObject.h"

class BikkuriMark : public IGameObject
{
public:
	BikkuriMark();
	~BikkuriMark();

	/// <summary>
	/// ビックリマークの更新関数。
	/// </summary>
	void Update();

	/// <summary>
	/// 座標を設定。
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
private:
	SkinModelRender* m_skinModel = nullptr;				//スキンモデル
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
};

