#include "stdafx.h"
#include "Stage.h"
#include "GameClear.h"
#include "GameOver.h"

const int GAMECLEAR_TIME = 20;				//�Q�[���N���A��\������^�C���B
const int GAMEOVER_TIME = 1;				//�Q�[���I�[�o�[��\������^�C���B

Stage::~Stage()
{
	DeleteGO(m_gameClear);
	DeleteGO(m_gameOver);
}

void Stage::LocalUpdate()
{
	//�X�e�[�W�P�̓T����S���߂܂���A�G��S���|������Q�[���N���A�B
	if (m_getSaruCount == m_saruNo && m_downEnemyCount == m_downEnemyNo)
	{
		m_gameClearTimer++;
		if (m_gameClearTimer == GAMECLEAR_TIME) {
			m_gameClear = NewGO<GameClear>();
		}
	}
	//�X�e�[�W�P��HP���Ȃ��Ȃ�����Q�[���I�[�o�[�B
	else if (m_gameOverFlag == true) 
	{
		m_gameOverTimer++;
		if (m_gameOverTimer == GAMECLEAR_TIME) {
			m_gameOver = NewGO<GameOver>();
		}
	}
}
