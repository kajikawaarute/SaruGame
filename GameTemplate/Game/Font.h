#pragma once

class Font
{
public:
	/// <summary>
	/// フォントのコンストラクタ
	/// </summary>
	Font();
	/// <summary>
	/// フォントのデストラクタ
	/// </summary>
	~Font();

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="text">テキスト</param>
	/// <param name="position">座標</param>
	/// <param name="color">カラー</param>
	/// <param name="scale">拡大率</param>
	/// <param name="pivot">ピボット</param>
	/// <param name="rotation">回転</param>
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
	DirectX::SpriteBatch* m_spriteBatch = nullptr;	//スプライトバッチ
	DirectX::SpriteFont* m_spriteFont = nullptr;	//フォント
	CVector2 m_screenSize = CVector2::Zero();		//スクリーンサイズ
};

