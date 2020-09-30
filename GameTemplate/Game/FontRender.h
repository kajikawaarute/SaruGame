#pragma once
#include "IGameObject.h"
#include "Font.h"

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
	/// フォントレンダーの描画関数
	/// </summary>
	/// <param name="text">表示させる文字</param>
	void DrawScreen(const wchar_t* text);
private:
	Font m_font;								//フォント
	CVector2 m_position = CVector2::Zero();		//座標
	CVector4 m_color = CVector4::White();		//カラー
	CVector2 m_scale = CVector2::One();			//拡大率
	CVector2 m_pivot = CVector2::Zero();		//ピボット	
	float m_rotation = 0.0f;					//回転
};

