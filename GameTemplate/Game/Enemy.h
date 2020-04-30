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
	/// �G�l�~�[�̍��W��ݒ�
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	CVector3& SetPos(CVector3 pos)
	{
		return m_position = pos;
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

	/// <summary>
	/// �|���ꂽ�Ƃ��̏���
	/// </summary>
	void Delete();

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

	enum EnAnimationClip {
		enAnim_taiki,						//�ҋ@�A�j���[�V����
		enAnim_walk,						//�����A�j���[�V����
		enAnim_num							//�A�j���[�V�����̐�
	};
	EnAnimationClip m_enAnimClip;

	Animation m_animation;							//�A�j���[�V����
	AnimationClip m_animationClip[enAnim_num];		//�A�j���[�V�����N���b�v
	const float m_animTime = 0.2f;					//�A�j���[�V�����̕�Ԏ���


	Player* m_pl = nullptr;					//�v���C���[�̃C���X�^���X
	
	int m_taikiTimer = 0;					//�ҋ@��ԂɂȂ�܂ł̃^�C�}�[
};

