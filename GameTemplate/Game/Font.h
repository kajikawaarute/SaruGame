#pragma once

class Font
{
public:
	/// <summary>
	/// �t�H���g�̃R���X�g���N�^
	/// </summary>
	Font();
	/// <summary>
	/// �t�H���g�̃f�X�g���N�^
	/// </summary>
	~Font();

	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="text">�e�L�X�g</param>
	/// <param name="position">���W</param>
	/// <param name="color">�J���[</param>
	/// <param name="scale">�g�嗦</param>
	/// <param name="pivot">�s�{�b�g</param>
	/// <param name="rotation">��]</param>
	/// <param name="effects"></param>
	void DrawScreenPos(
		wchar_t const* text,
		const CVector2& position,
		const CVector4& color = CVector4::White(),
		const CVector2& scale = CVector2::One(),
		const CVector2& pivot = CVector2::Zero(),
		float rotation = 0.0f,
		DirectX::SpriteEffects effects = DirectX::SpriteEffects_None
	);
private:
	DirectX::SpriteBatch* m_spriteBatch = nullptr;	//�X�v���C�g�o�b�`
	DirectX::SpriteFont* m_spriteFont = nullptr;	//�t�H���g
	CVector2 m_screenSize = CVector2::Zero();		//�X�N���[���T�C�Y
};

