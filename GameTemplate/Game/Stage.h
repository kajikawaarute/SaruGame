#pragma once
#include "StageBase.h"

class Stage : public StageBase
{
public:
	const wchar_t* GetCMOFilePath() const override
	{
		return L"Assets/modelData/stage_01.cmo";
	}
	void LocalUpdate() override;
};

