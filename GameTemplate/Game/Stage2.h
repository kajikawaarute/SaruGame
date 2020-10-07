#pragma once
#include "StageBase.h"

class Stage2 : public StageBase
{
public:
	
	const wchar_t* GetCMOFilePath() const override
	{
		return L"Assets/modelData/stage_02.cmo";
	}
	void LocalUpdate()override;

};

