#pragma once
#include "character/CharacterController.h"

#include "PlayerStateWait.h"
#include "PlayerStateMove.h"
#include "PlayerStateSaruGet.h"
#include "PlayerStateAttacked.h"
#include "PlayerStateJump.h"
#include "PlayerStateSliped.h"
#include "PlayerStateAttack.h"
#include "PlayerStateDeath.h"

class Saru;
class Enemy;
class GunEnemy;
class PlayerHP;
class Player : public IGameObject
{
public:
	Player();
	~Player();

	/// <summary>
	/// �v���C���[��Update�֐��O�ɌĂ΂��J�n�֐�
	/// </summary>
	/// <returns>true��Ԃ��ƈ�x�����Ă΂��</returns>
	bool Start();

	/// <summary>
	/// �v���C���[�̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �v���C���[�̈ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// �v���C���[�̍��W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void Setposition(const CVector3& pos)
	{
		m_position = pos;
		m_charaCon.SetPosition(m_position);
	}

	/// <summary>
	/// �v���C���[�̍��W���擾
	/// </summary>
	/// <returns></returns>
	CVector3& GetPos()
	{
		return m_position;
	}

	/// <summary>
	/// �v���C���[�̉�]��ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// �v���C���[�̉�]���擾
	/// </summary>
	/// <returns></returns>
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

	/// <summary>
	/// �T���̃C���X�^���X��ݒ�B
	/// </summary>
	/// <param name="saru">�T���̃C���X�^���X</param>
	void SetSaru(Saru* saru)
	{
		m_sarus.push_back(saru);
	}

	/// <summary>
	/// �G�l�~�|�̃C���X�^���X���擾�B
	/// </summary>
	/// <param name="enemy">�G�l�~�|�̃C���X�^���X</param>
	void SetEnemy(Enemy* enemy)
	{
		m_enemys.push_back(enemy);
	}

	/// <summary>
	/// �K���G�l�~�[�̃C���X�^���X��ݒ�B
	/// </summary>
	/// <param name="gunEnemy">�K���G�l�~�[�̃C���X�^���X</param>
	void SetGunEnemy(GunEnemy* gunEnemy)
	{
		m_gunEnemys.push_back(gunEnemy);
	}

	/// <summary>
	/// �v���C���[HP�̃C���X�^���X��ݒ�B
	/// </summary>
	/// <param name="playerHp">���C���[HP�̃C���X�^���X</param>
	void SetPlayerHP(PlayerHP* playerHp)
	{
		m_playerHp = playerHp;
	}

	/// <summary>
	/// �T���������Ƃ��̏���
	/// </summary>
	/// <param name="saru">�T���̃C���X�^���X</param>
	void DeleteSaru(Saru* saru);

	/// <summary>
	/// �G�l�~�[���������̏���
	/// </summary>
	/// <param name="enemy">�T���̃C���X�^���X</param>
	void DeleteEnemy(Enemy* enemy);

	/// <summary>
	/// �K���G�l�~�[���������̏���
	/// </summary>
	/// <param name="gunEnemy">�K���G�l�~�[�̃C���X�^���X</param>
	void DeleteGunEnemy(GunEnemy* gunEnemy);

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
	/// ���S���Ă���Ƃ��̏�Ԃɂ���B
	/// </summary>
	void StateDeath();

	/// <summary>
	/// ��Ԃ������Ă����Ԃɂ���B
	/// </summary>
	void SetStateSliped()
	{
		m_enPlayerState = enState_sliped;
	}

	/// <summary>
	/// �߂܂����T���J�E���g���擾�B
	/// </summary>
	/// <returns>�߂܂����T��</returns>
	const int& GetSaruCount()
	{
		return m_saruCount;
	}

	/// <summary>
	/// �|�����G�l�~�[�J�E���g���擾�B
	/// </summary>
	/// <returns>�|�����G�l�~�[</returns>
	const int& GetEnemyCount()
	{
		return m_enemyCount;
	}

	/// <summary>
	/// �A�j���[�V�����̍Đ����I�������ҋ@��Ԃɐ؂�ւ���
	/// </summary>
	void ChangeStateWaitAnim();

	/// <summary>
	/// �n�ʂɂ����Ƃ��ɑҋ@��Ԃɐ؂�ւ���B
	/// </summary>
	void ChangeStateWaitIsOnGound();
	/// <summary>
	/// ������΂��̗͂�ݒ肷��B
	/// </summary>
	/// <param name="attackedPower"></param>
	void SetAttackedPower(const CVector3& attackedPower)
	{
		m_attackedPower = attackedPower;
	}
private:
	friend class PlayerStateWait;
	friend class PlayerStateMove;
	friend class PlayerStateSaruGet;
	friend class PlayerStateJump;
	friend class PlayerStateSliped;
	friend class PlayerStateAttack;
	friend class PlayerStateDeath;
	friend class PlayerStateAttacked;

	SkinModelRender* m_skinModel = nullptr;				//�X�L�����f��									
	CVector3 m_position = CVector3::Zero();				//���W
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
	CVector3 m_attackedPower = CVector3::Zero();		//�U����H������Ƃ��̐�����΂��́B
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[

	enum EnAnimationClip {
		enAnim_wait,		//�ҋ@�A�j���[�V����
		enAnim_walk,		//�����A�j���[�V����
		enAnim_saruGet,		//�T���̕ߊl�A�j���[�V����
		enAnim_attacked,	//�U�����ꂽ�Ƃ��̃A�j���[�V����
		enAnim_jump,		//�W�����v���Ă��鎞�̃A�j���[�V����
		enAnim_sliped,		//�����Ă��鎞�̃A�j���[�V����
		enAnim_attack,		//�U���A�j���[�V����
		enAnim_death,		//���S�A�j���[�V����
		enAnim_num			//�A�j���[�V�����N���b�v�̐�
	};
	Animation m_animation;								//�A�j���[�V����
	AnimationClip m_animationClip[enAnim_num];			//�A�j���[�V�����N���b�v
	EnAnimationClip m_enAnimClip;

	enum EnPlayerState {
		enState_wait,		//�ҋ@���
		enState_walk,		//�������
		enState_saruGet,	//�T����ߊl
		enState_attacked,	//�U�����ꂽ���
		enState_Jump,		//�W�����v���
		enState_sliped,		//�����Ă�����
		enState_attack,		//�U�����
		enState_death		//���S���
	};
	EnPlayerState m_enPlayerState = enState_wait;

	IPlayerState* m_currentState = nullptr;		//���݂̃v���C���[�̏��
	PlayerStateWait m_playerStateWait;			//�ҋ@���
	PlayerStateMove m_playerStateMove;			//�ړ����
	PlayerStateSaruGet m_playerStateSaruGet;	//�T����ߊl
	PlayerStateAttacked m_playerStateAttacked;	//�U�����ꂽ���
	PlayerStateJump m_playerStateJump;			//�W�����v���
	PlayerStateSliped m_playerStateSliped;		//�����Ă�����
	PlayerStateAttack m_playerStateAttack;		//�U�����
	PlayerStateDeath m_playerStateDeath;		//���S���
	
	int m_saruCount = 0;					//�T����߂܂�����
	int m_enemyCount = 0;					//�G�l�~�[��|������

	const float animTime = 0.2f;			//�A�j���[�V�����̕�Ԏ���

	std::vector<Saru*> m_sarus;				//�T���̃��X�g
	std::vector<Enemy*> m_enemys;			//�G�l�~�[�̃��X�g
	std::vector<GunEnemy*> m_gunEnemys;		//�K���G�l�~�[�̃��X�g

	PlayerHP* m_playerHp = nullptr;			//�v���C���[HP�̃C���X�^���X

public:
	/// <summary>
	/// ��Ԃ�؂�ւ��鏈���B
	/// </summary>
	/// <param name="nextState">�v���C���[�̏��</param>
	void ChangeState(EnPlayerState nextState);
};

