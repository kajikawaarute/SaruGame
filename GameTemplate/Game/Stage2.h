#pragma once
#include "StageBase.h"

class GameClear;
class GameOver;
class Stage2 : public StageBase
{
public:
	~Stage2();

	/// <summary>
	/// .cmo�t�@�C���̃t�@�C���p�X���擾�B
	/// </summary>
	/// <returns>�X�e�[�W�̃t�@�C���p�X</returns>
	const wchar_t* GetCMOFilePath() const override
	{
		return L"Assets/modelData/stage_02.cmo";
	}

	/// <summary>
	/// �X�e�[�W�Q�ŗL�̍X�V�֐��B
	/// </summary>
	void LocalUpdate()override;
private:
	GameClear* m_gameClear = nullptr;	//�Q�[���I�[�o�[�̃C���X�^���X
	GameOver* m_gameOver = nullptr;		//�Q�[���I�[�o�[�̃C���X�^���X
};

