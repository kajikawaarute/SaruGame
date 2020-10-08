#pragma once

class SaruCounter : public IGameObject
{
public:
	SaruCounter();
	~SaruCounter();

	/// <summary>
	/// �T���J�E���^�[��Update�֐��O�ɌĂ΂��J�n�֐��B
	/// </summary>
	/// <returns>true��Ԃ��ƈ�x�����Ă΂��</returns>
	bool Start();

	/// <summary>
	/// �T���J�E���^�[�̍X�V�֐��B
	/// </summary>
	void Update();

	/// <summary>
	/// �T���J�E���^�[�̕`��֐��B
	/// </summary>
	void Draw();

	/// <summary>
	/// �߂܂����T���̐����J�E���g����B
	/// </summary>
	/// <param name="saruCount">�߂܂����T���̐�</param>
	void AddSaruCounter(int saruCount)
	{
		m_saruCounter = saruCount;
	}

	/// <summary>
	/// �T���̐���ݒ�B
	/// </summary>
	/// <param name="saruNo">�T���̐�</param>
	void SetSaruNumber(int saruNo)
	{
		m_saruCount = saruNo;
	}

private:
	FontRender* m_fontRender = nullptr;				//�t�H���g�̃C���X�^���X

	CVector2 m_fontPosition = { 20.0f, 100.0f };	//�t�H���g�̍��W
	CVector2 m_fontScale = { 0.7f, 0.7f };			//�t�H���g�̊g�嗦

	int m_saruCount = 0;		//�T���̐�
	int m_saruCounter = 0;		//�߂܂����T���̐�

	wchar_t m_text[64];			//�e�L�X�g
};

