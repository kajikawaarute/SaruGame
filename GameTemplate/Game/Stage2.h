#pragma once
#include "StageBase.h"

class GameClear;
class GameOver;
class Stage2 : public StageBase
{
public:
	~Stage2();

	/// <summary>
	/// .cmoファイルのファイルパスを取得。
	/// </summary>
	/// <returns>ステージのファイルパス</returns>
	const wchar_t* GetCMOFilePath() const override
	{
		return L"Assets/modelData/stage_02.cmo";
	}

	/// <summary>
	/// ステージ２固有の更新関数。
	/// </summary>
	void LocalUpdate()override;
private:
	GameClear* m_gameClear = nullptr;	//ゲームオーバーのインスタンス
	GameOver* m_gameOver = nullptr;		//ゲームオーバーのインスタンス
};

