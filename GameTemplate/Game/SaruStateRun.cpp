#include "stdafx.h"
#include "SaruStateRun.h"
#include "Saru.h"

void SaruStateRun::OnEnter()
{
}

void SaruStateRun::Update()
{
	m_saru->StateRun();
}

void SaruStateRun::OnLeave()
{
}
