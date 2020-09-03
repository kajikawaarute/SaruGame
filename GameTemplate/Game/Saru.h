#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "SaruStateWait.h"
#include "SaruStateRun.h"
#include "SaruStateAttack.h"
#include "SaruStateGet.h"
#include "SaruStateStun.h"
#include "SaruStateFound.h"

class Player;
class BananaPeel;
class BikkuriMark;
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
	/// �T���̑��������̏���
	/// </summary>
	void Run();

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
	/// �����������̏���
	/// </summary>
	void Found();

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
	void SetPos(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �T���̉�]��ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
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

	/// <summary>
	/// �v���C���[�̃C���X�^���X��ݒ�B
	/// </summary>
	/// <param name="player">�v���C���[�̃C���X�^���X</param>
	void SetPlayer(Player* player)
	{
		m_pl = player;
	}

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
	/// ����������Ԃɐݒ�
	/// </summary>
	void ChangeStateFound()
	{
		m_enSaruState = enState_found;
	}

	/// <summary>
	/// ���񂾏�Ԃɐݒ�B
	/// </summary>
	void ChangeStateStun()
	{
		m_enSaruState = enState_stun;
	}

	/// <summary>
	/// �߂܂���ꂽ���ɌĂ΂��֐�
	/// </summary>
	void Death();

	/// <summary>
	/// �A�j���[�V�����̍Đ����I�������ҋ@��Ԃɐ؂�ւ���
	/// </summary>
	void ChangeStateWaitAnim();

	/// <summary>
	/// �T�����߂܂���ꂽ���̃T�E���h���Đ�����
	/// </summary>
	void SaruGetSound();

	/// <summary>
	/// �T�����v���C���[�Ɍ����������̃T�E���h���Đ�����B
	/// </summary>
	void SaruFoundSound();

	/// <summary>
	/// �ݒ肳�ꂽ���W���p�X���X�g�ɓo�^
	/// </summary>
	/// <param name="m_pos"></param>
	void PushPathPosition(CVector3 m_pos)
	{
		m_pathList.push_back(m_pos);
	}
private:
	friend class SaruStateWait;
	friend class SaruStateRun;
	friend class SaruStateAttack;
	friend class SaruStateGet;
	friend class SaruStateStun;
	friend class SaruStateFound;

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
		enAnim_found,			//�����������̃A�j���[�V����
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
		enState_stun,				//�Ђ�񂾏��
		enState_found				//�����������
	};
	EnSaruState m_enSaruState;

	ISaruState* m_currentState = nullptr;	//���݂̃T���̏��
	SaruStateWait m_saruStateWait;			//�ҋ@���
	SaruStateRun m_saruStateRun;			//������
	SaruStateAttack m_saruStateAttack;		//�U�����
	SaruStateGet m_saruStateGet;			//�ߊl���
	SaruStateStun m_saruStateStun;			//���ݏ��
	SaruStateFound m_saruStateFound;		//�����������

	Player* m_pl = nullptr;					//�v���C���[�̃C���X�^���X
	BananaPeel* m_banaPeel = nullptr;		//�o�i�i�̔�̃C���X�^���X
	BikkuriMark* m_bikkuriMark = nullptr;

	int m_waitTimer = 0;		//�ҋ@��ԂɂȂ�܂ł̃^�C�}�[
	int m_banaPeelTimer = 0;	//�o�i�i�̔�𓊂���܂ł̃^�C�}�[
	int pathNum = 0;			//�p�X�̔ԍ�
	float angle = 0.0f;

	std::vector<CVector3> m_pathList;		//�p�X�̃��X�g

	const float m_animTime = 0.2f;			//�A�j���[�V�����̕�Ԏ���

	Effekseer::Effect* m_saruGetEffekt = nullptr;		//�߂܂���ꂽ���̃G�t�F�N�g
	Effekseer::Effect* m_saruRunEffect = nullptr;		//�����Ă��鎞�̃G�t�F�N�g
	Effekseer::Effect* m_saruDamegeEffect = nullptr;
	Effekseer::Handle m_playEffectHandle = -1;

public:
	/// <summary>
	/// ��Ԃ�؂�ւ��鏈���B
	/// </summary>
	/// <param name="nextState">�T���̏��</param>
	void ChangeState(EnSaruState nextState);
};

