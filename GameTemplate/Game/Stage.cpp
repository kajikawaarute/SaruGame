#include "stdafx.h"
#include "Stage.h"
#include "IGameObjectManager.h"
#include "GameClear.h"
#include "GameOver.h"

const int GAMECLEAR_TIME = 20;				//ゲームクリアを表示するタイム。
const int GAMEOVER_TIME = 1;				//ゲームオーバーを表示するタイム。

Stage::~Stage()
{
	g_goMgr.DeleteGO(m_gameClear);
	g_goMgr.DeleteGO(m_gameOver);
}

void Stage::LocalUpdate()
{
	//ステージ１はサルを全員捕まえたらゲームクリア。
	if (m_getSaruCount == m_saruNo)
	{
		m_gameClearTimer++;
		if (m_gameClearTimer == GAMECLEAR_TIME) {
			m_gameClear = g_goMgr.NewGO<GameClear>();
		}
	}
	//ステージ１はHPがなくなったらゲームオーバー。
	if (m_gameOverFlag == true) 
	{
		m_gameOverTimer++;
		if (m_gameOverTimer == GAMECLEAR_TIME) {
			m_gameOver = g_goMgr.NewGO<GameOver>();
		}
	}
}
