#include "stdafx.h"
#include "Stage2.h"
#include "GameClear.h"
#include "GameOver.h"

const int GAMECLEAR_TIME = 30;				//�Q�[���N���A��\������^�C���B
const int GAMEOVER_TIME = 1;				//�Q�[���I�[�o�[��\������^�C���B

Stage2::~Stage2()
{
	g_goMgr.DeleteGO(m_gameClear);
}

void Stage2::LocalUpdate()
{
	//�X�e�[�W�Q�̓T����S���߂܂�����Q�[���N���A�B
	if (m_getSaruCount == m_saruNo)
	{
		m_gameClearTimer++;
		if (m_gameClearTimer == GAMECLEAR_TIME) {
			m_gameClear = g_goMgr.NewGO<GameClear>();
		}
	}

	//�X�e�[�W�Q�̓v���C���[��HP���Ȃ��Ȃ�����Q�[���I�[�o�[�B
	if (m_gameOverFlag == true)
	{
		m_gameOverTimer++;
		if (m_gameOverTimer == GAMEOVER_TIME) {
			m_gameOver = g_goMgr.NewGO<GameOver>();
		}
	}
}
