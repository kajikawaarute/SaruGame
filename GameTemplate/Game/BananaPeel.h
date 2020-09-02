#pragma once
#include "IGameObject.h"
#include "physics/PhysicsGhostObject.h"

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
	/// �o�i�i�̔���������̏���
	/// </summary>
	void Delete();

	/// <summary>
	///	���W��ݒ�
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns></returns>
	CVector3& GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// �ړ����x��ݒ�
	/// </summary>
	/// <param name="move"></param>
	void SetMoveSpd(CVector3 move)
	{
		m_moveSpeed += move;
	}

	/// <summary>
	/// �ړ����x���擾
	/// </summary>
	/// <returns></returns>
	CVector3 GetMoveSpd()
	{
		return m_moveSpeed;
	}

	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();				//���W
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	PhysicsGhostObject m_ghost;							//�S�[�X�g�I�u�W�F�N�g
	Player* m_pl = nullptr;								//�v���C���[�̃C���X�^���X
	int m_deathTimer = 0;								//������܂ł̃^�C�}�[
	int m_stopTimer = 0;								//�~�܂�܂ł̃^�C�}�[
};

