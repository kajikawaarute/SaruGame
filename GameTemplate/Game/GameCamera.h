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

	/// <summary>
	/// �v���C���[�̃C���X�^���X��ݒ�B
	/// </summary>
	/// <param name="player">�v���C���[�̃C���X�^���X</param>
	void SetPlayer(Player* player)
	{
		pl = player;
	}
private:
	Player* pl = nullptr;		//�v���C���[�̃C���X�^���X
	CVector3 m_toCameraPos;		//�J�����̍��W
};

