#include "stdafx.h"
#include "FontRender.h"


FontRender::FontRender()
{
}

FontRender::~FontRender()
{
}

void FontRender::Update()
{
}

void FontRender::DrawScreen(const wchar_t* text)
{
	m_font.DrawScreenPos(
		text,
		m_position,
		m_color,
		m_scale,
		m_pivot,
		m_rotation,
		DirectX::SpriteEffects_None
	);
}
