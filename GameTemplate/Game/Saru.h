#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "SaruStateWait.h"
#include "SaruStateRun.h"
#include "SaruStateAttack.h"
#include "SaruStateGet.h"
#include "SaruStateStun.h"

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
	/// �Ђ�񂾎��̏���
	/// </summary>
	void Stun();

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
	/// �ҋ@�^�C�}�[���擾
	/// </summary>
	/// <returns></returns>
	int GetWaitTimer()
	{
		return m_waitTimer;
	}
	/// <summary>
	/// �ҋ@�^�C�}�[�����Z
	/// </summary>
	/// <returns></returns>
	int AddWaitTimer()
	{
		return m_waitTimer++;
	}

	/// <summary>
	/// �ҋ@�^�C�}�[�����Z�b�g
	/// </summary>
	/// <returns></returns>
	int ReSetWaitTimer()
	{
		return m_waitTimer = 0;
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
	/// �U������܂ł̋���
	/// </summary>
	void AttackDistance();

	/// <summary>
	/// �ҋ@��Ԃɐݒ�
	/// </summary>
	void ChangeStateWait()
	{
		m_enSaruState = enState_wait;
	}

	/// <summary>
	/// �����Ԃɐݒ�
	/// </summary>
	void ChangeStateRun()
	{
		m_enSaruState = enState_run;
	}

	/// <summary>
	/// �߂܂���ꂽ���ɌĂ΂��֐�
	/// </summary>
	void Death();

	/// <summary>
	/// �A�j���[�V�����̍Đ����I�������ҋ@��Ԃɐ؂�ւ���
	/// </summary>
	void ChangeStateWaitAnim();
private:
	friend class SaruStateWait;
	friend class SaruStateRun;
	friend class SaruStateGet;
	friend class SaruStateStun;

	SkinModel m_model;									//�X�L�����f��
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
	
	enum EnAnimationClip {
		enAnim_wait,			//�ҋ@�A�j���[�V����
		enAnim_run,				//����A�j���[�V����
		enAnim_attack,			//�U���A�j���[�V����
		enAnim_Get,				//�ߊl�A�j���[�V����
		enAnim_stun,			//�Ђ��ł���A�j���[�V����
		enAnim_num				//�A�j���[�V�����N���b�v�̐�
	};
	Animation m_animation;								//�A�j���[�V����
	AnimationClip m_animClip[enAnim_num];				//�A�j���[�V�����N���b�v
	EnAnimationClip m_enAnimClip;

	enum EnSaruState {
		enState_wait,				//�ҋ@���
		enState_run,				//������
		enState_attack,				//�U�����
		enState_Get,				//�ߊl���
		enState_stun				//�Ђ�񂾏��
	};
	EnSaruState m_enSaruState;

	ISaruState* m_currentState = nullptr;	//���݂̃T���̏��
	SaruStateWait m_saruStateWait;			//�ҋ@���
	SaruStateRun m_saruStateRun;			//������
	SaruStateAttack m_saruStateAttack;		//�U�����
	SaruStateGet m_saruStateGet;			//�ߊl���
	SaruStateStun m_saruStateStun;			//���ݏ��

	Player* m_pl = nullptr;					//�v���C���[�̃C���X�^���X
	BananaPeel* m_banaPeel = nullptr;		//�o�i�i�̔�̃C���X�^���X

	int m_waitTimer = 0;		//�ҋ@��ԂɂȂ�܂ł̃^�C�}�[
	int m_deathTimer = 0;		//�ߊl�����܂ł̃^�C�}�[
	int m_banaPeelTimer = 0;	//�o�i�i�̔�𓊂���܂ł̃^�C�}�[
	int m_stunTimer = 0;

	const float m_animTime = 0.2f;			//�A�j���[�V�����̕�Ԏ���

	//Effekseer�}�l�[�W���[�Ǘ�
	Effekseer::Manager* m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_effekt = nullptr;		//�G�t�F�N�g
	Effekseer::Handle m_playEffectHandle = -1;

	//CSoundSource m_saru_getAmiSE;			//�ߊl���ꂽ�Ƃ���SE
	//CSoundSource m_saru_attackSE;			//�U�������Ƃ���SE
public:
	void ChangeState(EnSaruState nextState);
};

