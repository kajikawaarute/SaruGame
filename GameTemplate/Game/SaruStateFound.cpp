#include "stdafx.h"
#include "SaruStateFound.h"
#include "Saru.h"

void SaruStateFound::OnEnter()
{
}

void SaruStateFound::Update()
{
	m_saru->Found();
}

void SaruStateFound::OnLeave()
{
}
