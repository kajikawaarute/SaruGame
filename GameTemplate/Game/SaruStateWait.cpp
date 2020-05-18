#include "stdafx.h"
#include "SaruStateWait.h"
#include "Saru.h"

void SaruStateWait::OnEnter()
{
}

void SaruStateWait::Update()
{
	m_saru->StateWait();
}

void SaruStateWait::OnLeave()
{
}
