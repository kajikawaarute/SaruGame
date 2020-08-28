#include "stdafx.h"
#include "SaruStateFound.h"
#include "Saru.h"

void SaruStateFound::OnEnter()
{
	m_saru->SaruFoundSound();
}

void SaruStateFound::Update()
{
	m_saru->Found();
}

void SaruStateFound::OnLeave()
{
}
