#pragma once
#include "IGameObject.h"

class Player;
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
	/// �T�����߂܂���ꂽ���̏���
	/// </summary>
	void GetSaru();

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
	AnimationClip m_animClip[2];						//�A�j���[�V�����N���b�v
	enum EnAnimationClip {
		enAnim_taiki,			//�ҋ@�A�j���[�V����
		enAnim_run,				//����A�j���[�V����
		enAnim_num				//�A�j���[�V�����N���b�v�̐�
	};
	EnAnimationClip m_enAnimClip;
	Player* m_pl = nullptr;		//�v���C���[�̃C���X�^���X
};

