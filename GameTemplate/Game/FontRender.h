#pragma once
#include "IGameObject.h"
#include "Font.h"

class FontRender : public IGameObject
{
public:
	FontRender();
	~FontRender();
	/// <summary>
	/// �t�H���g�����_�[�̍X�V�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �t�H���g�����_�[�̕`��֐�
	/// </summary>
	/// <param name="text">�\�������镶��</param>
	void DrawScreen(const wchar_t* text);
private:
	Font m_font;								//�t�H���g
	CVector2 m_position = CVector2::Zero();		//���W
	CVector4 m_color = CVector4::White();		//�J���[
	CVector2 m_scale = CVector2::One();			//�g�嗦
	CVector2 m_pivot = CVector2::Zero();		//�s�{�b�g	
	float m_rotation = 0.0f;					//��]
};

