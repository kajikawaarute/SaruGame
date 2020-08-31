#pragma once
#include "IGameObject.h"

#include "GunEnemyStateWait.h"
#include "GunEnemyStateAttack.h"
#include "GunEnemyStateFound.h"

class Player;
class GunEnemyBullet;
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
	/// <summary>
	/// �K���G�l�~�[�̍U������
	/// </summary>
	void Attack();

	/// <summary>
	/// �U������܂ł̋���
	/// </summary>
	void AttackDistance();

	/// <summary>
	/// �����������̏���
	/// </summary>
	void Found();

	void SetPlayer(Player* player)
	{
		m_player = player;
	}
private:
	friend class GunEnemyStateWait;
	friend class GunEnemyStateAttack;
	friend class GunEnemyStateFound;

	IGunEnemyState* m_currentState = nullptr;	//���݂̃K���G�l�~�[�̏��
	GunEnemyStateWait m_gunEnemyStateWait;		//�ҋ@���
	GunEnemyStateAttack m_gunEnemyStateAttack;	//�U�����
	GunEnemyStateFound m_gunEnemyStateFound;	//�����������

	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x

	enum EnGunEnemyState {
		enState_wait,	//�ҋ@���
		enState_attack,	//�U�����
		enState_found	//�����������
	};
	EnGunEnemyState m_enGunEnemyState;	//�K���G�l�~�[�̏��

	enum EnAnimationClip {
		enAnim_wait,			//�ҋ@�A�j���[�V����
		enAnim_attack,			//�U���A�j���[�V����
		enAnim_found,			//�����������̃A�j���[�V����
		enAnim_num				//�A�j���[�V�����N���b�v�̐�
	};
	Animation m_animation;					//�A�j���[�V����
	AnimationClip m_animClip[enAnim_num];	//�A�j���[�V�����N���b�v
	EnAnimationClip m_enAnimClip;			//�A�j���[�V�����̏��
	const float m_animTime = 0.2f;			//�A�j���[�V������Ԏ���

	int m_bulletTimer = 0;			//�e�����܂ł̎���
	bool m_foundFlag = false;		//�����������̔���

	Player* m_player = nullptr;		//�v���C���[�̃C���X�^���X
public:
	/// <summary>
	/// ��Ԃ�؂�ւ��鏈��
	/// </summary>
	/// <param name="nextState">�K���G�l�~�[�̏��</param>
	void ChangeState(EnGunEnemyState nextState);
};

