#include "stdafx.h"
#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
	m_shadowMapRT.Create(2048, 2048, DXGI_FORMAT_R32_FLOAT);
}


ShadowMap::~ShadowMap()
{
}

void ShadowMap::UpdateShadowMap(CVector3 lightCameraPos, CVector3 lightCameraTarget)
{
	m_lightCameraPosition = lightCameraPos + g_camera3D.GetPosition();
	m_lightCameraTarget = lightCameraTarget + g_camera3D.GetTarget();

	//ライトの方向を計算する。
	auto lightDir = m_lightCameraTarget - m_lightCameraPosition;
	if (lightDir.Length() < 0.0001f) {
		//ライトカメラの注視点と視点が近い
		std::abort();
	}
	lightDir.Normalize();
	//ライトの方向によって、ライトカメラの上方向を決める。
	CVector3 lightCameraUpAxis;
	if (fabsf(lightDir.y) > 0.99998f) {
		lightCameraUpAxis = CVector3::AxisX();
	}
	else {
		lightCameraUpAxis = CVector3::AxisY();
	}
	//ライトビュー行列を計算
	m_lightViewMatrix.MakeLookAt(
		m_lightCameraPosition,
		m_lightCameraTarget,
		lightCameraUpAxis
	);
	//ライトプロジェクション行列を作成
	m_lightProjMatrix.MakeOrthoProjectionMatrix(
		3000,
		3000,
		0.1f,
		5000.0f
	);
}

void ShadowMap::Draw()
{
	//シャドウマップにレンダリング
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;

	d3dDeviceContext->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);

	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);

	//シャドウマップにレンダリング
	RenderToShadowMap();

	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);

	oldRenderTargetView->Release();
	oldDepthStencilView->Release();
}

void ShadowMap::RenderToShadowMap()
{
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	
	//レンダリングターゲットを切り替える

	ID3D11RenderTargetView* rts[] = {
		m_shadowMapRT.GetRenderTargetView()
	};
	d3dDeviceContext->OMSetRenderTargets(1, rts, m_shadowMapRT.GetDepthStensilView());

	
	//ビューポートを設定
	d3dDeviceContext->RSSetViewports(1, m_shadowMapRT.GetViewport());
	//シャドウマップをクリア
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_shadowMapRT.ClearRenderTarget(clearColor);

	//シャドウキャスターをシャドウマップにレンダリング。
	for (auto& caster : m_shadowCasters) {
		caster->Draw(
			enRenderMode_CreateShadowMap,
			m_lightViewMatrix,
			m_lightProjMatrix
		);
	}
	m_shadowCasters.clear();
}
