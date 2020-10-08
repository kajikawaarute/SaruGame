#pragma once

class FontRender : public IGameObject
{
public:
	FontRender();
	~FontRender();
	/// <summary>
	/// フォントレンダーの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// テキストを設定。
	/// </summary>
	/// <param name="text">表示させる文字</param>
	void SetText(const wchar_t* text);
	
	/// <summary>
	/// 座標を設定。
	/// </summary>
	void SetPosition(const CVector2& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// 回転を設定。
	/// </summary>
	void SetRotation(float rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// カラーを設定。
	/// </summary>
	void SetColor(const CVector4& color)
	{
		m_color = color;
	}

	/// <summary>
	/// 拡大率を設定。
	/// </summary>
	void SetScale(const CVector2& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// ピボットを設定。
	/// </summary>
	void SetPivot(const CVector2& pivot)
	{
		m_pivot = pivot;
	}
private:
	Font m_font;								//フォント
	CVector2 m_position = CVector2::Zero();		//座標
	CVector4 m_color = CVector4::White();		//カラー
	CVector2 m_scale = CVector2::One();			//拡大率
	CVector2 m_pivot = CVector2::Zero();		//ピボット	
	float m_rotation = 0.0f;					//回転
};

