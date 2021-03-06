#pragma once

/// <summary>
/// レンダリングモード。
/// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//不正なレンダリングモード。
	enRenderMode_CreateShadowMap,	//シャドウマップ生成。
	enRenderMode_ToonRender,		//トゥーンレンダー
	enRenderMode_Normal,			//通常レンダリング。
	enRenderMode_Num,				//レンダリングモードの数。
};

/*!
 *@brief	グラフィックスエンジン。
 */
class GraphicsEngine
{
private:
	GraphicsEngine();
	~GraphicsEngine();

public:
	/// <summary>
	/// グラフィックスエンジンのインスタンスを取得。
	/// </summary>
	/// <returns>グラフィックスエンジンのインスタンス</returns>
	static GraphicsEngine* GetInstance()
	{
		static GraphicsEngine* instance = nullptr;
		if (instance == nullptr) {
			instance = new GraphicsEngine();
		}
		return instance;
	}

	/*!
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}

	/// <summary>
	/// デプスステンシルビューを取得。
	/// </summary>
	/// <returns>デプスステンシルビュー</returns>
	ID3D11DepthStencilView* GetDepthStencilView()
	{
		return m_depthStencilView;
	}

	/// <summary>
	/// スプライトバッチを取得。
	/// </summary>
	/// <returns></returns>
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_spriteBatch.get();
	}
	/// <summary>
	/// スプライトフォントを取得
	/// </summary>
	/// <returns></returns>
	DirectX::SpriteFont* GetSpriteFont()
	{
		return m_spriteFont.get();
	}
	/// <summary>
	/// D3D11デバイスを取得
	/// </summary>
	/// <returns></returns>
	ID3D11Device* GetDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */
	void EndRender();
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;		//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;		//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = NULL;		//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//デプスステンシルビュー。

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;		//スプライトフォント

};

//ヘルパー関数

/// <summary>
/// D3D11デバイスを取得。
/// </summary>
/// <returns>D3D11デバイス</returns>
static inline ID3D11Device* GetD3DDeviceGraphicsEngine()
{
	return GraphicsEngine::GetInstance()->GetD3DDevice();
}

/// <summary>
/// D3D11デバイスコンテキストを取得。
/// </summary>
/// <returns>D3D11デバイスコンテキスト</returns>
static inline ID3D11DeviceContext* GetD3DDeviceContextGraphicsEngine()
{
	return GraphicsEngine::GetInstance()->GetD3DDeviceContext();
}

/// <summary>
/// スプライトバッチを取得。
/// </summary>
/// <returns>スプライトバッチ</returns>
static inline DirectX::SpriteBatch* GetSpriteBatchGraphicsEngine()
{
	return GraphicsEngine::GetInstance()->GetSpriteBatch();
}

/// <summary>
/// スプライトフォントを取得。
/// </summary>
/// <returns>スプライトフォント</returns>
static inline DirectX::SpriteFont* GetSpriteFontGraphicsEngine()
{
	return GraphicsEngine::GetInstance()->GetSpriteFont();
}