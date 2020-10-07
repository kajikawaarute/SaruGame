#include "stdafx.h"
#include "Stage.h"

void Stage::LocalUpdate()
{
	//ステージ１はサルを全員捕まえたらゲームクリア
	/*if (m_pl->GetSaruCount() == m_saruNo)
	{
		m_gameClearTimer++;
		if (m_gameClearTimer == GAMECLEAR_TIME) {
			m_gameClear = g_goMgr.NewGO<GameClear>();
		}
		if (m_gameClearTimer == GAMECLEAR_TITLE_TIME) {
			g_goMgr.DeleteGO(this);
		}
	}*/
}
