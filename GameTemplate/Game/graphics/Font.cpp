#include "stdafx.h"
#include "Font.h"

Font::Font()
{
	m_spriteBatch = GetSpriteBatchGraphicsEngine();
	m_spriteFont = GetSpriteFontGraphicsEngine();

	m_screenSize.x = FRAME_BUFFER_W;
	m_screenSize.y = FRAME_BUFFER_H;
}

Font::~Font()
{
}

void Font::DrawScreenPos(
	wchar_t const * text, 
	const CVector2 & position, 
	const CVector4 & color, 
	const CVector2 & scale, 
	const CVector2 & pivot, 
	float rotation, 
	DirectX::SpriteEffects effects)
{
	m_spriteBatch->Begin();
	m_spriteFont->DrawString(
		m_spriteBatch,
		text,
		position.vec,
		color,
		rotation,
		DirectX::XMFLOAT2(pivot.x, pivot.y),
		DirectX::XMFLOAT2(scale.x, scale.y),
		effects
	);
	m_spriteBatch->End();
}
