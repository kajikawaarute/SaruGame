#include "stdafx.h"
#include "Stage2.h"
#include "GameClear.h"
#include "GameOver.h"

const int GAMECLEAR_TIME = 30;				//ゲームクリアを表示するタイム。
const int GAMEOVER_TIME = 1;				//ゲームオーバーを表示するタイム。

Stage2::~Stage2()
{
	g_goMgr.DeleteGO(m_gameClear);
}

void Stage2::LocalUpdate()
{
	//ステージ２はサルを全員捕まえたらゲームクリア。
	if (m_getSaruCount == m_saruNo)
	{
		m_gameClearTimer++;
		if (m_gameClearTimer == GAMECLEAR_TIME) {
			m_gameClear = g_goMgr.NewGO<GameClear>();
		}
	}

	//ステージ２はプレイヤーのHPがなくなったらゲームオーバー。
	if (m_gameOverFlag == true)
	{
		m_gameOverTimer++;
		if (m_gameOverTimer == GAMEOVER_TIME) {
			m_gameOver = g_goMgr.NewGO<GameOver>();
		}
	}
}
