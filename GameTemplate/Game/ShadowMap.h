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
	/// </summary>
	/// <param name="shadowCaster">シャドウキャスター</param>
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}
private:
	CVector3 m_lightCameraPosition = CVector3::Zero();		//ライトカメラの視点
	CVector3 m_lightCameraTarget = CVector3::Zero();		//ライトカメラの注視点
	CMatrix	 m_lightViewMatrix = CMatrix::Identity();		//ライトビュー行列
	CMatrix  m_lightProjMatrix = CMatrix::Identity();		//ライトプロジェクション行列
	RenderTarget m_shadowMapRT;								//シャドウマップを描画するレンダリングターゲット。
	std::vector<SkinModel* > m_shadowCasters;				//シャドウキャスターの配列
};