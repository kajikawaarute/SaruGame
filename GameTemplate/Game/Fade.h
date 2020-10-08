#pragma once

class Fade : public IGameObject
{
public:
	Fade();
	~Fade();

	/// <summary>
	/// フェードの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// フェードの描画関数
	/// </summary>
	void Draw();

	/// <summary>
	///  SpriteBatctの描画関数。
	/// </summary>
	void SpriteBatctDraw();

	/// <summary>
	/// フェードイン
	/// </summary>
	void StartFadeIn()
	{
		m_state = enState_FadeIn;
	}
	/// <summary>
	/// フェードアウト
	/// </summary>
	void StartFadeOut()
	{
		m_state = enState_FadeOut;
	}

private:
	DirectX::SpriteBatch* m_spriteBatch;					//スプライトバッチ

	ID3D11Device* m_device;									//構築済み
	ID3D11DeviceContext* m_deviceContext;					//構築済み
	ID3D11ShaderResourceView* m_shaderResourceView;			//読み込んだ画像ファイルの保存先

	float m_positionX = 0.0f;		//画像のX座標
	float m_positionY = 0.0f;		//画像のY座標
	float m_rotation = 0.0f;		//画像の回転
	float m_scale = 2.5f;			//拡大率
	float m_depth = 0.0f;			//スプライトの深度

	enum EnState {
		enState_FadeIn,		//フェードイン中。
		enState_FadeOut,	//フェードアウト中。
		enState_Idle,		//アイドル中。
	};
	EnState m_state = enState_Idle;	//状態

	float m_alpha = 0.0f;				//アルファ値
	float m_alphaIncAmount = 0.06f;		//アルファ値の量
};

