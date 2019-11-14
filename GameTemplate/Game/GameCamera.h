#pragma once
#include "IGameObject.h"
#include "Player.h"
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	void Update();
	void Draw();
	void SetPlayer(Player* player)
	{
		pl = player;
	}
private:
	Player* pl = nullptr;		//�v���C���[�̃C���X�^���X
	CVector3 m_toCameraPos;
};

