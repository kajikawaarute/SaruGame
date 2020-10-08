#pragma once
#include "Player.h"

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	/// <summary>
	/// �Q�[���J�����̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �v���C���[�̃C���X�^���X��ݒ�B
	/// </summary>
	/// <param name="player">�v���C���[�̃C���X�^���X</param>
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
private:
	Player* m_player = nullptr;		//�v���C���[�̃C���X�^���X
	CVector3 m_toCameraPos;			//�J�����̍��W
};