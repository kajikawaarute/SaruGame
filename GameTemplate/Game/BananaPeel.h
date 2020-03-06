#pragma once
#include "IGameObject.h"
#include "PhysicsGhostObject.h"

class Player;
class BananaPeel : public IGameObject
{
public:
	BananaPeel();
	~BananaPeel();
	void Update();
	void Draw();
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	void Slip(CQuaternion rotation)
	{
		rotation = { 0.0f, 5.0f, 0.0f, 1.0f };
	}
	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();				//ç¿ïW
	CQuaternion m_rotation = CQuaternion::Identity();	//âÒì]
	CVector3 m_scale = CVector3::One();					//ägëÂó¶
	int m_timer = 0;
	PhysicsGhostObject m_ghost;
	Player* m_pl = nullptr;
};

