#include "stdafx.h"
#include "Stage.h"
#include "IGameObjectManager.h"
#include "GameClear.h"
#include "GameOver.h"

const int GAMECLEAR_TIME = 20;				//�Q�[���N���A��\������^�C���B
const int GAMEOVER_TIME = 1;				//�Q�[���I�[�o�[��\������^�C���B

Stage::~Stage()
{
	g_goMgr.DeleteGO(m_gameClear);
	g_goMgr.DeleteGO(m_gameOver);
}

void Stage::LocalUpdate()
{
	//�X�e�[�W�P�̓T����S���߂܂�����Q�[���N���A�B
	if (m_getSaruCount == m_saruNo)
	{
		m_gameClearTimer++;
		if (m_gameClearTimer == GAMECLEAR_TIME) {
			m_gameClear = g_goMgr.NewGO<GameClear>();
		}
	}
	//�X�e�[�W�P��HP���Ȃ��Ȃ�����Q�[���I�[�o�[�B
	if (m_gameOverFlag == true) 
	{
		m_gameOverTimer++;
		if (m_gameOverTimer == GAMECLEAR_TIME) {
			m_gameOver = g_goMgr.NewGO<GameOver>();
		}
	}
}
