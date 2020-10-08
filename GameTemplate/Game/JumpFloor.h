#pragma once

#include "physics/PhysicsStaticObject.h"
#include "physics/PhysicsGhostObject.h"
#include "character/CharacterController.h"

class Player;
class JumpFloor : public IGameObject
{
public:
	JumpFloor();
	~JumpFloor();
	/// <summary>
	/// �V�����v��̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �S�[�X�g�I�u�W�F�N�g�̍��W��ݒ�
	/// </summary>
	/// <param name="pos">�S�[�X�g�I�u�W�F�N�g�̍��W</param>
	void SetPositonGhost(const CVector3 pos)
	{
		m_ghost.SetPosition(pos);
	}

	/// <summary>
	/// �ÓI�I�u�W�F�N�g�̍쐬
	/// </summary>
	void CreateStaticObject();

	/// <summary>
	/// �v���C���[�̃C���X�^���X��ݒ�B
	/// </summary>
	/// <param name="player"></param>
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
private:
	SkinModelRender* m_skinModel= nullptr;						//�X�L�����f��
	CVector3 m_position = CVector3::Zero();						//���W
	CQuaternion m_rotation = CQuaternion::Identity();			//��]
	CVector3 m_scale = CVector3::One();							//�g�嗦
	CVector3 m_ghostObjectScale = { 450.0f, 60.0f, 400.0f };	//�S�[�X�g�I�u�W�F�N�g�̊g�嗦

	PhysicsGhostObject m_ghost;							//�S�[�X�g�I�u�W�F�N�g
	PhysicsStaticObject m_static;						//�ÓI�I�u�W�F�N�g

	enum EnAnimationClip {
		enAnim_wait,		//�W�����v��̑ҋ@�A�j���[�V����
		enAnim_jump,		//�W�����v��A�j���[�V����
		enAnim_num			//�A�j���[�V�����N���b�v�̐�
	};

	Animation m_animation;								//�A�j���[�V����
	AnimationClip m_animationClip[enAnim_num];			//�A�j���[�V�����N���b�v
	EnAnimationClip m_enAnimClip;

	Player* m_player = nullptr;							//�v���C���[�̃C���X�^���X
};

