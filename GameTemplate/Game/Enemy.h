#pragma once
#include "IGameObject.h"
#include "character/CharacterController.h"

class Player;
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();
	/// <summary>
	/// �G�l�~�[�̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �G�l�~�[�̈ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// �G�l�~�[�̕`��֐�
	/// </summary>
	void Draw();

	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
private:
	SkinModel m_model;									//�X�L�����f��
	CVector3 m_position = {0.0f, 0.0f, 300.0f};			//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
	Player* m_pl = nullptr;								//�v���C���[�̃C���X�^���X

};

