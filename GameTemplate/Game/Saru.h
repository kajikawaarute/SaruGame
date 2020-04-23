#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

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
	/// �T�����߂܂���ꂽ���̏���
	/// </summary>
	void GetSaru();

	/// <summary>
	/// �T���̍U������
	/// </summary>
	void Attack();

	/// <summary>
	/// �T���̉�]����
	/// </summary>
	void Turn();

	/// <summary>
	/// �o�i�i�̔�𓊂��鎞�̏���
	/// </summary>
	void BanaPeelThrow();

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

	void SetPlayer(Player* player)
	{
		m_pl = player;
	}
	/// <summary>
	/// Effekser�̏�����
	/// </summary>
	void InitEffekseer();
	/// <summary>
	/// Effekseer�J����
	/// </summary>
	void EffekseerCamera();

	/// <summary>
	/// �T������v���C���[�܂ł̋���
	/// </summary>
	void Distance();
private:
	SkinModel m_model;									//�X�L�����f��
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
	Animation m_animation;								//�A�j���[�V����
	AnimationClip m_animClip[4];						//�A�j���[�V�����N���b�v
	enum EnAnimationClip {
		enAnim_taiki,			//�ҋ@�A�j���[�V����
		enAnim_run,				//����A�j���[�V����
		enAnim_attack,			//�U���A�j���[�V����
		enAnim_Get,				//�ߊl�A�j���[�V����
		enAnim_num				//�A�j���[�V�����N���b�v�̐�
	};
	enum EnSaruSaruState {
		enState_taiki,				//�ҋ@���
		enState_run,				//������
		enState_attack,				//�U�����
		enState_Get,				//�ߊl���
		enState_num					//��Ԃ̐�
	};

	EnAnimationClip m_enAnimClip;
	EnSaruSaruState m_enSaruState;

	Player* m_pl = nullptr;					//�v���C���[�̃C���X�^���X
	BananaPeel* m_banaPeel = nullptr;		//�o�i�i�̔�̃C���X�^���X

	int m_taikiTimer = 0;		//�ҋ@��ԂɂȂ�܂ł̃^�C�}�[
	int m_deathTimer = 0;		//�ߊl�����܂ł̃^�C�}�[
	int m_banaPeelTimer = 0;		//�o�i�i�̔�𓊂���܂ł̃^�C�}�[

	const float m_animTime = 0.2f;			//�A�j���[�V�����̕�Ԏ���

	//Effekseer�}�l�[�W���[�Ǘ�
	Effekseer::Manager* m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_effekt = nullptr;		//�G�t�F�N�g
	Effekseer::Handle m_playEffectHandle = -1;

	//CSoundSource m_saru_getAmiSE;			//�ߊl���ꂽ�Ƃ���SE
	//CSoundSource m_saru_attackSE;			//�U�������Ƃ���SE
};

