#pragma once
#include "IGameObject.h"

class Sky : public IGameObject
{
public:
	Sky();
	~Sky();
	void Update();
	void Draw();

	/// <summary>
	/// ‹ó‚ÌÀ•W‚ğİ’è
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ‹ó‚Ì‰ñ“]‚ğİ’è
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}
private:
	SkinModel m_model;									//ƒ‚ƒfƒ‹

	CVector3 m_position = CVector3::Zero();				//À•W
	CQuaternion m_rotation = CQuaternion::Identity();	//‰ñ“]
	CVector3 m_scale = CVector3::One();					//Šg‘å—¦
};

