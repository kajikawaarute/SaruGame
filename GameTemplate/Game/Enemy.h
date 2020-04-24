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
	/// �G�l�~�[�̕`��֐�
	/// </summary>
	void Draw();

	/// <summary>
	/// �G�l�~�[�̍��W���擾
	/// </summary>
	/// <returns>���W</returns>
	CVector3& GetPos()
	{
		return m_position;
	}

	/// <summary>
	/// �G�l�~�[�̈ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// �G�l�~�[�̉�]����
	/// </summary>
	void Turn();

	//�G�l�~�[�̍U������
	void Attack();
	
	/// <summary>
	/// �U������܂ł̋���
	/// </summary>
	void AttackDistance();

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

	enum EnEnemyState {
		enState_taiki,			//�ҋ@���
		enState_move,			//�ړ����
		enState_attack,			//�U�����
	};
	EnEnemyState m_enEnemyState;

	Animation m_animation;					//�A�j���[�V����
	AnimationClip m_animationClip[1];		//�A�j���[�V�����N���b�v
	enum EnAnimationClip {
		enAnim_walk,						//�����A�j���[�V����
		enAnim_num							//�A�j���[�V�����̐�
	};
	EnAnimationClip m_enAnimClip;

	Player* m_pl = nullptr;					//�v���C���[�̃C���X�^���X
	
	int m_taikiTimer = 0;					//�ҋ@��ԂɂȂ�܂ł̃^�C�}�[
};

