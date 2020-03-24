#pragma once
#include "IGameObject.h"
#include "PhysicsGhostObject.h"

class Player;
class BananaPeel : public IGameObject
{
public:
	BananaPeel();
	~BananaPeel();

	/// <summary>
	/// �o�i�i�̔�̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �o�i�i�̔�̕`��֐�
	/// </summary>
	void Draw();

	/// <summary>
	///	���W��ݒ�
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	int m_deathTimer = 0;								//������܂ł̃J�E���g
	PhysicsGhostObject m_ghost;							//�S�[�X�g�I�u�W�F�N�g
	Player* m_pl = nullptr;								//�v���C���[�̃C���X�^���X
};

