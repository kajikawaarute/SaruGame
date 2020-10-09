#pragma once
class EnemyCounter : public IGameObject
{
public:
	EnemyCounter();
	~EnemyCounter();

	/// <summary>
	/// �G�l�~�|�J�E���^�[��Update�֐��O�ɌĂ΂��X�V�֐��B
	/// </summary>
	/// <returns>true��Ԃ��ƈ�x�����Ă΂��</returns>
	bool Start();

	/// <summary>
	/// �G�l�~�[�J�E���^�[�̍X�V�֐��B
	/// </summary>
	void Update();

	/// <summary>
	/// �G�l�~�[�J�E���^�[�̕`��֐��B
	/// </summary>
	void Draw();

	/// <summary>
	/// �|�����G�l�~�|�̐����J�E���g����B
	/// </summary>
	/// <param name="eneCounter">�|�����G�l�~�|�̐�</param>
	void AddEnemyCounter(const int &eneCounter)
	{
		m_enemyCounter = eneCounter;
	}

	/// <summary>
	/// �G�l�~�[�̐���ݒ�B
	/// </summary>
	/// <param name="eneNo">�G�l�~�[�̐�</param>
	void SetEnemyNumber(const int &eneNo)
	{
		m_enemyCount = eneNo;
	}
private:
	FontRender* m_fontRender = nullptr;				//�t�H���g�̃C���X�^���X

	CVector2 m_fontPosition = { 20.0f, 150.0f };	//�t�H���g�̍��W
	CVector2 m_fontScale = { 0.7f, 0.7f };			//�t�H���g�̊g�嗦

	int m_enemyCount = 0;		//�G�l�~�|�̐�
	int m_enemyCounter = 0;		//�|�����G�l�~�|�̐�

	wchar_t m_text[64];			//�e�L�X�g
};

