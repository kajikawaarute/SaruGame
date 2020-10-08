#pragma once
#include "StageBase.h"

class GameClear;
class GameOver;
class Stage : public StageBase
{
public:
	~Stage();

	/// <summary>
	/// .cmoファイルのファイルパスを取得。
	/// </summary>
	/// <returns>ステージのファイルパス</returns>
	const wchar_t* GetCMOFilePath() const override
	{
		return L"Assets/modelData/stage_01.cmo";
	}

	/// <summary>
	/// ステージ１固有の更新関数。
	/// </summary>
	void LocalUpdate() override;
private:
	GameClear* m_gameClear = nullptr;	//ゲームクリアのインスタンス
	GameOver* m_gameOver = nullptr;		//ゲームオーバーのインスタンス
};

