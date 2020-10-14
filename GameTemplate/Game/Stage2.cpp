#include "stdafx.h"
#include "Stage2.h"
#include "GameClear.h"
#include "GameOver.h"

const int GAMECLEAR_TIME = 30;				//�Q�[���N���A��\������^�C���B
const int GAMEOVER_TIME = 1;				//�Q�[���I�[�o�[��\������^�C���B

Stage2::~Stage2()
{
	DeleteGO(m_gameClear);
	DeleteGO(m_gameOver);
}

void Stage2::LocalUpdate()
{
	//�X�e�[�W�Q�̓T����S���߂܂��A�G����萔�|������Q�[���N���A�B
	if (m_getSaruCount == m_saruNo && m_downEnemyCount >= m_downEnemyNo)
	{
		m_gameClearTimer++;
		if (m_gameClearTimer == GAMECLEAR_TIME) {
			m_gameClear = NewGO<GameClear>();
		}
	}

	//�X�e�[�W�Q�̓v���C���[��HP���Ȃ��Ȃ�����Q�[���I�[�o�[�B
	if (m_gameOverFlag == true)
	{
		m_gameOverTimer++;
		if (m_gameOverTimer == GAMEOVER_TIME) {
			m_gameOver = NewGO<GameOver>();
		}
	}
}
