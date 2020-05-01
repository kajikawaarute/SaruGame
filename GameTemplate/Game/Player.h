#pragma once
#include "character/CharacterController.h"
#include "IGameObject.h"
#include "PhysicsGhostObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Saru;
class Enemy;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	/// <summary>
	/// �v���C���[�̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �v���C���[�̈ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// �v���C���[�̕`��֐�
	/// </summary>
	void Draw();

	/// <summary>
	/// �v���C���[�̍��W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void Setposition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �v���C���[�̍��W���擾
	/// </summary>
	/// <returns></returns>
	CVector3& GetPos()
	{
		return m_position;
	}

	CQuaternion& GetRot()
	{
		return m_rotation;
	}

	/// <summary>
	/// �v���C���[�̈ړ����x���擾
	/// </summary>
	/// <returns></returns>
	CVector3& GetMoveSpd()
	{
		return m_moveSpeed;
	}

	/// <summary>
	/// �L�����N�^�[�R���g���[���[���擾
	/// </summary>
	/// <returns></returns>
	CharacterController& GetcharaCon()
	{
		return m_charaCon;
	}

	/// <summary>
	/// �T����߂܂������̏���
	/// </summary>
	void GetSaru();

	/// <summary>
	/// �v���C���[�̉�]����
	/// </summary>
	void Turn();

	void SetSaru(Saru* saru)
	{
		m_sarus.push_back(saru);
	}
	void SetEnemy(Enemy* enemy)
	{
		m_enemys.push_back(enemy);
	}

	/// <summary>
	/// �T���������Ƃ��̏���
	/// </summary>
	/// <param name="saru"></param>
	void DeleteSaru(Saru* saru);

	/// <summary>
	/// �G�l�~�[���������̏���
	/// </summary>
	/// <param name="enemy"></param>
	void DeleteEnemy(Enemy* enemy);

	/// <summary>
	/// �U�����ꂽ�Ƃ��̏���
	/// </summary>
	void Attacked();

	/// <summary>
	/// �o�i�i�̔�Ŋ��������̏���
	/// </summary>
	void Sliped();

	/// <summary>
	/// �W�����v���Ă��鎞�̏���
	/// </summary>
	void Jump();

	/// <summary>
	/// �T����ߊl���悤�Ƃ��Ă��鏈��
	/// </summary>
	void SaruGet();

	/// <summary>
	/// �U�����悤�Ƃ��Ă��鎞�̏���
	/// </summary>
	void AttackTry();

	/// <summary>
	/// �U�����Ă��鎞�̏���
	/// </summary>
	void Attack();

	/// <summary>
	/// ��Ԃ������Ă����Ԃɂ���B
	/// </summary>
	void SetStateSliped()
	{
		m_enPlayerState = enState_sliped;
	}

	void SetPlayerWalkSE();

	int GetSaruCount()
	{
		return m_saruCount;
	}
private:
	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();				//���W
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[

	PhysicsGhostObject m_ghost;							//�S�[�X�g�I�u�W�F�N�g
	enum EnAnimationClip {
		enAnim_taiki,		//�ҋ@�A�j���[�V����
		enAnim_walk,		//�����A�j���[�V����
		enAnim_saruGet,		//�T���̕ߊl�A�j���[�V����
		enAnim_attacked,	//�U�����ꂽ�Ƃ��̃A�j���[�V����
		enAnim_jump,		//�W�����v���Ă��鎞�̃A�j���[�V����
		enAnim_sliped,		//�����Ă��鎞�̃A�j���[�V����
		enAnim_attack,		//�U���A�j���[�V����
		enAnim_num			//�A�j���[�V�����N���b�v�̐�
	};
	Animation m_animation;								//�A�j���[�V����
	AnimationClip m_animationClip[enAnim_num];			//�A�j���[�V�����N���b�v

	enum EnPlayerState {
		enState_taiki,		//�ҋ@���
		enState_walk,		//�������
		enState_saruGet,	//�T����ߊl
		enState_attacked,	//�U�����ꂽ���
		enState_Jump,		//�W�����v���
		enState_sliped,		//�����Ă�����
		enState_attack,		//�U�����
	};
	EnAnimationClip m_enAnimClip;

	EnPlayerState m_enPlayerState;
	
	int m_saruCount = 0;					//�T����߂܂�����

	const float animTime = 0.2f;			//�A�j���[�V�����̕�Ԏ���

	std::vector<Saru*> m_sarus;
	std::vector<Enemy*> m_enemys;
};

