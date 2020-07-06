#pragma once
#include "RenderTarget.h"

class ShadowMap
{
private:
	ShadowMap();
public:
	static ShadowMap& GetInstance()
	{
		static ShadowMap instance;
		return instance;
	}
	~ShadowMap();
	/// <summary>
	/// シャドウマップを更新
	/// </summary>
	void UpdateShadowMap(CVector3 lightCameraPos, CVector3 lightCameraTarget);

	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// シャドウマップにシャドウキャスターをレンダリング。
	/// </summary>
	void RenderToShadowMap();

	/// <summary>
	/// シャドウキャスターを登録。
	/// シャドウキャスターは影を落とす側。
	/// </summary>
	/// <param name="shadowCaster">シャドウキャスター</param>
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}

	/// <summary>
	/// シャドウマップのSRVを取得。
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetShadowMapSRV()
	{
		return m_shadowMapRT.GetRenderTargetSRV();
	}

	/// <summary>
	/// ライトビュー行列を取得
	/// </summary>
	/// <returns></returns>
	CMatrix GetLightViewMatrix() const
	{
		return m_lightViewMatrix;
	}

	/// <summary>
	/// ライトプロジェクション行列を取得。
	/// </summary>
	/// <returns></returns>
	CMatrix GetLightProjMatrix() const
	{
		return m_lightProjMatrix;
	}

	/// <summary>
	/// ライトカメラの視点を取得。
	/// </summary>
	/// <returns></returns>
	CVector3 GetLightCameraPosition()
	{
		return m_lightCameraPosition;
	}

	/// <summary>
	/// ライトカメラの注視点を取得。
	/// </summary>
	/// <returns></returns>
	CVector3 GetLightCameraTarget()
	{
		return m_lightCameraTarget;
	}

	/// <summary>
	/// ライトカメラの視点を設定。
	/// </summary>
	/// <param name="ligCameraPos"></param>
	void SetLightCameraPosition(CVector3 ligCameraPos)
	{
		m_lightCameraPosition = ligCameraPos;
	}

	/// <summary>
	/// ライトカメラの注視点を設定。
	/// </summary>
	/// <param name="ligCameraTarget"></param>
	void SetLightCameraTarget(CVector3 ligCameraTarget)
	{
		m_lightCameraTarget = ligCameraTarget;
	}
private:
	CVector3 m_lightCameraPosition = CVector3::Zero();		//ライトカメラの視点
	CVector3 m_lightCameraTarget = CVector3::Zero();		//ライトカメラの注視点
	CMatrix	 m_lightViewMatrix = CMatrix::Identity();		//ライトビュー行列
	CMatrix  m_lightProjMatrix = CMatrix::Identity();		//ライトプロジェクション行列
	RenderTarget m_shadowMapRT;								//シャドウマップを描画するレンダリングターゲット。
	std::vector<SkinModel* > m_shadowCasters;				//シャドウキャスターの配列
};