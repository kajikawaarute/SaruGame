#include "stdafx.h"
#include "SaruStateGet.h"
#include "Saru.h"

void SaruStateGet::OnEnter()
{
}

void SaruStateGet::Update()
{
	m_saru->GetSaru();
}

void SaruStateGet::OnLeave()
{
}