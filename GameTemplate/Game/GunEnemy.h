#pragma once
#include "IGameObject.h"

class Player;
class GunEnemy : public IGameObject
{
public:
	GunEnemy();
	~GunEnemy();

	/// <summary>
	/// �K���G�l�~�[�̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �K���G�l�~�[�̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �K���G�l�~�[�̍��W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	/// <returns></returns>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �K���G�l�~�[�̉�]��ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}

	void SetPlayer(Player* player)
	{
		m_player = player;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦

	Player* m_player = nullptr;					//�v���C���[�̃C���X�^���X
};

