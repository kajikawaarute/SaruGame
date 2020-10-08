#pragma once
#include "physics/PhysicsGhostObject.h"

class Player;
class GunEnemyBullet : public IGameObject
{
public:
	GunEnemyBullet();
	~GunEnemyBullet();

	/// <summary>
	/// �K���G�l�~�[�o���b�g�̔�̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �K���G�l�~�[�o���b�g���������̏���
	/// </summary>
	void Delete();

	/// <summary>
	///	���W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns>���W</returns>
	CVector3& GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// �ړ����x��ݒ�
	/// </summary>
	/// <param name="move">�ړ����x</param>
	void SetMoveSpd(CVector3 move)
	{
		m_moveSpeed += move;
	}

	/// <summary>
	/// �ړ����x���擾
	/// </summary>
	/// <returns>�ړ����x</returns>
	CVector3 GetMoveSpd()
	{
		return m_moveSpeed;
	}

	/// <summary>
	/// �v���C���[�̃C���X�^���X��ݒ�B
	/// </summary>
	/// <param name="player">�v���C���[�̃C���X�^���X</param>
	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
private:
	SkinModelRender* m_skinModel = nullptr;					//�X�L�����f��
	CVector3 m_position = CVector3::Zero();					//���W
	CVector3 m_moveSpeed = CVector3::Zero();				//�ړ����x
	CQuaternion m_rotation = CQuaternion::Identity();		//��]
	CVector3 m_scale = CVector3::One();						//�g�嗦
	CVector3 m_ghostObjectScale = { 50.0f, 50.0f, 50.0f };	//�S�[�X�g�I�u�W�F�N�g�̊g�嗦

	PhysicsGhostObject	m_ghostObject;					//�S�[�X�g�I�u�W�F�N�g
	Player* m_pl = nullptr;								//�v���C���[�̃C���X�^���X
	int m_deathTimer = 0;								//������܂ł̃^�C�}�[
};

