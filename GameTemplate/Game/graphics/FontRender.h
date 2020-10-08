#pragma once

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
	/// �e�L�X�g��ݒ�B
	/// </summary>
	/// <param name="text">�\�������镶��</param>
	void SetText(const wchar_t* text);
	
	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	void SetPosition(const CVector2& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	void SetRotation(float rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// �J���[��ݒ�B
	/// </summary>
	void SetColor(const CVector4& color)
	{
		m_color = color;
	}

	/// <summary>
	/// �g�嗦��ݒ�B
	/// </summary>
	void SetScale(const CVector2& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// �s�{�b�g��ݒ�B
	/// </summary>
	void SetPivot(const CVector2& pivot)
	{
		m_pivot = pivot;
	}
private:
	Font m_font;								//�t�H���g
	CVector2 m_position = CVector2::Zero();		//���W
	CVector4 m_color = CVector4::White();		//�J���[
	CVector2 m_scale = CVector2::One();			//�g�嗦
	CVector2 m_pivot = CVector2::Zero();		//�s�{�b�g	
	float m_rotation = 0.0f;					//��]
};

