#pragma once
#include "physics/PhysicsStaticObject.h"

/// <summary>
/// �X�e�[�W���Ƃɓ��ꏈ��������\�����l�����āA���N���X��p�ӁB 
/// </summary>
class StageBase : public IGameObject
{
public:
	StageBase();
	~StageBase();

	/// <summary>
	/// StageBase��Update�֐��O�ɌĂ΂��J�n�֐��B
	/// </summary>
	/// <returns>true��Ԃ��ƈ�x�����Ă΂��</returns>
	bool Start() override;

	/// <summary>
	/// StageBase�̍X�V�֐��B
	/// </summary>
	void Update() override;

	/// <summary>
	/// �X�e�[�W�ŗL�̍X�V�������L�q�B
	/// </summary>
	virtual void LocalUpdate() 
	{
	}

	/// <summary>
	/// .cmo�t�@�C���̃t�@�C���p�X���擾�B
	/// </summary>
	/// <returns>�X�e�[�W�̃t�@�C���p�X</returns>
	virtual const wchar_t* GetCMOFilePath() const = 0;

	/// <summary>
	/// �X�e�[�W�̍��W��ݒ�B
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// �X�e�[�W�̉�]��ݒ�B
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(const CQuaternion rot)
	{
		 m_rotation = rot;
	}

	/// <summary>
	/// �T���̐���ݒ�B
	/// </summary>
	/// <param name="saruNo">�T���̐�</param>
	 void SetSaruNo(const int &saruNo)
	 {
		 m_saruNo = saruNo;
	 }

	 /// <summary>
	 /// �|���G�l�~�[�̐���ݒ�B
	 /// </summary>
	 /// <param name="eneNo">�G�l�~�[�̐�</param>
	 void SetDownEnemyNo(const int &eneNo)
	 {
		 m_downEnemyNo = eneNo;
	 }

	 /// <summary>
	 /// �߂܂����T���̐���ݒ�B
	 /// </summary>
	 /// <param name="saruCount">�߂܂����T���̐�</param>
	 void SetSaruCounter(const int &saruCount)
	 {
		 m_getSaruCount = saruCount;
	 }

	 /// <summary>
	 /// �|�����G�l�~�[�̐���ݒ�B
	 /// </summary>
	 /// <param name="eneCount">�|�����G�l�~�[�̐�</param>
	 void SetDownEnemyCounter(const int &eneCount)
	 {
		 m_downEnemyCount = eneCount;
	 }

	 /// <summary>
	 /// �Q�[���I�[�o�[�̃t���O��ݒ�B
	 /// </summary>
	 /// <param name="flag">�t���O</param>
	 /// <returns>�Q�[���I�[�o�[�̃t���O</returns>
	 bool SetGameOverFlag(bool flag)
	 {
		 m_gameOverFlag = flag;
		 return m_gameOverFlag;
	 }

	 /// <summary>
	 /// �Q�[���N���A�^�C�}�[���擾�B
	 /// </summary>
	 /// <returns>�Q�[���N���A�^�C�}�[</returns>
	 int GetClearTimer()
	 {
		 return m_gameClearTimer;
	 }

	 /// <summary>
	 /// �Q�[���I�[�o�[�^�C�}�[���擾�B
	 /// </summary>
	 /// <returns>�Q�[���I�[�o�[�^�C�}�[</returns>
	 int GetOverTimer()
	 {
		 return m_gameOverTimer;
	 }
protected:
	int m_saruNo = 0;				//�T���̐��B
	int m_getSaruCount = 0;			//�߂܂����T���̐��B
	int m_downEnemyNo = 0;			//�|���G�l�~�[�̐��B
	int m_downEnemyCount = 0;		//�|�����G�l�~�[�̐��B
	int m_gameClearTimer = 0;		//�Q�[���N���A�܂ł̃^�C�}�[
	int m_gameOverTimer = 0;		//�Q�[���I�[�o�[�̂܂ł̃^�C�}�[
	bool m_gameOverFlag = false;	//�Q�[���I�[�o�[�̃t���O
private:
	SkinModelRender* m_skinModel = nullptr;				//�X�L�����f��

	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_scale = CVector3::One();					//�g�嗦

	PhysicsStaticObject m_staticObject;		//�ÓI�I�u�W�F�N�g
};

