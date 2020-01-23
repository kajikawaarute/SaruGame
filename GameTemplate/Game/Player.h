#pragma once
#include "character/CharacterController.h"
#include "IGameObject.h"
#include "PhysicsGhostObject.h"

class Saru;
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
	/// <summary>
	/// �T����߂܂������̏���
	/// </summary>
	void GetSaru();

	void Fukitobi();

	/// <summary>
	/// �v���C���[�̉�]����
	/// </summary>
	void Turn();

	void SetSaru(Saru* saru)
	{
		m_sarus.push_back(saru);
	}
private:
	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();				//���W
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CQuaternion m_rotetion = CQuaternion::Identity();	//��]
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[

	PhysicsGhostObject m_ghost;							//�S�[�X�g�I�u�W�F�N�g
	Animation m_animation;								//�A�j���[�V����
	AnimationClip m_animationClip[3];					//�A�j���[�V�����N���b�v
	enum EnAnimationClip {
		enAnim_walk,		//�����A�j���[�V����
		enAnim_taiki,		//�ҋ@�A�j���[�V����
		enAnim_saruGet,		//�T���̕ߊl�A�j���[�V����
		enAnim_num			//�A�j���[�V�����N���b�v�̐�
	};
	EnAnimationClip m_enAnimClip;
	int m_timer = 0;
	bool m_flag = true;

	std::vector<Saru*> m_sarus ;
};

