#pragma once
#include "IGameObject.h"
#include "RenderTarget.h"

class ToonRender
{
private:
	ToonRender();
public:
	static ToonRender& GetInstance()
	{
		static ToonRender instance;
		return instance;
	}
	~ToonRender();
	
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// 深度値を書き込むためのパス
	/// </summary>
	void ZPrepass();

	/// <summary>
	/// トゥーンレンダーのSRVを取得
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetToonRenderSRV()
	{
		return m_toonRenderRT.GetRenderTargetSRV();
	}

	/// <summary>
	/// トゥーンレンダーを登録。
	/// </summary>
	/// <param name="toonRender">トゥーンレンダー</param>
	void RegistToonRender(SkinModel* toonRender)
	{
		m_toonRender.push_back(toonRender);
	}
private:
	RenderTarget m_toonRenderRT;				//深度値を出力する用のバッファ
	std::vector<SkinModel* > m_toonRender;		//トゥーンレンダーの配列
};

