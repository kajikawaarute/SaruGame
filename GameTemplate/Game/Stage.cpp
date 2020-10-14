#include "stdafx.h"
#include "Stage.h"
#include "GameClear.h"
#include "GameOver.h"

const int GAMECLEAR_TIME = 20;				//ゲームクリアを表示するタイム。
const int GAMEOVER_TIME = 1;				//ゲームオーバーを表示するタイム。

Stage::~Stage()
{
	DeleteGO(m_gameClear);
	DeleteGO(m_gameOver);
}

void Stage::LocalUpdate()
{
	//ステージ１はサルを全員捕まえる、敵を全部倒したらゲームクリア。
	if (m_getSaruCount == m_saruNo && m_downEnemyCount == m_downEnemyNo)
	{
		m_gameClearTimer++;
		if (m_gameClearTimer == GAMECLEAR_TIME) {
			m_gameClear = NewGO<GameClear>();
		}
	}
	//ステージ１はHPがなくなったらゲームオーバー。
	else if (m_gameOverFlag == true) 
	{
		m_gameOverTimer++;
		if (m_gameOverTimer == GAMECLEAR_TIME) {
			m_gameOver = NewGO<GameOver>();
		}
	}
}
