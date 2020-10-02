#pragma once
#include "IGameObject.h"

class Sky : public IGameObject
{
public:
	Sky();
	~Sky();

	/// <summary>
	/// 空の更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// 空の座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// 空の回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}
private:
	SkinModelRender* m_skinModel = nullptr;				//スキンモデル
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
};

