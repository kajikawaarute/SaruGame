#pragma once
#include "IGameObject.h"

class Player;
class BananaPeel;
class Saru : public IGameObject
{
public:
	Saru();
	~Saru();
	/// <summary>
	/// �T���̍X�V�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �T���̈ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// �T���̕`��֐�
	/// </summary>
	void Draw();
	/// <summary>
	/// �T���̍��W���擾
	/// </summary>
	/// <returns></returns>
	CVector3& GetPos()
	{
		return m_position;
	}
	/// <summary>
	/// �T���̍��W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	/// <returns></returns>
	CVector3& SetPos(CVector3 pos)
	{
		return m_position = pos;
	}
	/// <summary>
	/// �T�����߂܂���ꂽ���̏���
	/// </summary>
	void GetSaru();

	/// <summary>
	/// �T���̉�]����
	/// </summary>
	void Turn();

	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
private:
	SkinModel m_model;									//�X�L�����f��
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
	Animation m_animation;								//�A�j���[�V����
	AnimationClip m_animClip[3];						//�A�j���[�V�����N���b�v
	enum EnAnimationClip {
		enAnim_taiki,			//�ҋ@�A�j���[�V����
		enAnim_run,				//����A�j���[�V����
		enAnim_attack,			//�U���A�j���[�V����
		enAnim_num				//�A�j���[�V�����N���b�v�̐�
	};
	EnAnimationClip m_enAnimClip;
	Player* m_pl = nullptr;		//�v���C���[�̃C���X�^���X
	int m_timer = 0;
	int m_bananaCount = 0;
};

