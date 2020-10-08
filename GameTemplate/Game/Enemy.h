#pragma once
#include "character/CharacterController.h"
#include "EnemyStateAttack.h"
#include "EnemyStateWait.h"
#include "EnemyStateMove.h"

#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Player;
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	bool Start();

	/// <summary>
	/// �G�l�~�[�̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �G�l�~�[�̍��W���擾
	/// </summary>
	/// <returns>���W</returns>
	CVector3& GetPos()
	{
		return m_position;
	}
	/// <summary>
	/// �G�l�~�[�̍��W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	/// <returns></returns>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �G�l�~�[�̉�]��ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// �G�l�~�[�̈ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// �G�l�~�[�̉�]����
	/// </summary>
	void Turn();

	/// <summary>
	/// �U������܂ł̋���
	/// </summary>
	void AttackDistance();

	/// <summary>
	/// �|���ꂽ�Ƃ��̏���
	/// </summary>
	void Delete();

	/// <summary>
	/// �ҋ@�^�C�}�[�����Z
	/// </summary>
	/// <returns>�ҋ@�^�C�}�[</returns>
	int AddWaitTimer()
	{
		return m_waitTimer++;
	}
	/// <summary>
	/// �ҋ@�^�C�}�[���擾
	/// </summary>
	/// <returns>�ҋ@�^�C�}�[</returns>
	int GetWaitTimer()
	{
		return m_waitTimer;
	}
	/// <summary>
	/// �ҋ@�^�C�}�[�����Z�b�g
	/// </summary>
	/// <returns>�ҋ@�^�C�}�[</returns>
	int ReSetWaitTimer()
	{
		return m_waitTimer = 0;
	}

	/// <summary>
	/// �ҋ@��Ԃɐ؂�ւ���
	/// </summary>
	void ChangeStateWait()
	{
		m_enEnemyState = enState_wait;
	}

	/// <summary>
	/// �ړ���Ԃɐ؂�ւ���
	/// </summary>
	void ChangeStateMove()
	{
		m_enEnemyState = enState_move;
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
	friend class EnemyStateAttack;
	friend class EnemyStateWait;
	friend class EnemyStateMove;

	SkinModelRender* m_skinModel = nullptr;				//�X�L�����f��
	CVector3 m_position = {0.0f, 0.0f, 300.0f};			//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x

	CharacterController m_charaCon;

	enum EnEnemyState {
		enState_wait,			//�ҋ@���
		enState_move,			//�ړ����
		enState_attack,			//�U�����
	};
	EnEnemyState m_enEnemyState;

	enum EnAnimationClip {
		enAnim_wait,						//�ҋ@�A�j���[�V����
		enAnim_walk,						//�����A�j���[�V����
		enAnim_num							//�A�j���[�V�����̐�
	};
	EnAnimationClip m_enAnimClip;

	Animation m_animation;							//�A�j���[�V����
	AnimationClip m_animationClip[enAnim_num];		//�A�j���[�V�����N���b�v
	const float m_animTime = 0.2f;					//�A�j���[�V�����̕�Ԏ���


	Player* m_pl = nullptr;					//�v���C���[�̃C���X�^���X
	
	int m_waitTimer = 0;					//�ҋ@��ԂɂȂ�܂ł̃^�C�}�[

	IEnenyState* m_currentState = nullptr;	//���݂̃G�l�~�[�̏��
	EnemyStateAttack m_enemyStateAttack;	//�U�����
	EnemyStateWait m_enemyStateWait;		//�ҋ@���
	EnemyStateMove m_enemyStateMove;		//�ړ����

	Effekseer::Effect* m_enemyDeathEffekt = nullptr;	//�G�t�F�N�g�B
	Effekseer::Handle m_playEffectHandle = -1;

public:
	/// <summary>
	/// ��Ԃ�؂�ւ��鏈���B
	/// </summary>
	/// <param name="nextState">�G�l�~�|�̏��</param>
	void ChangeState(EnEnemyState nextState);
};

