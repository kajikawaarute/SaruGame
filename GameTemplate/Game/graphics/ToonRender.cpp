#include "stdafx.h"
#include "ToonRender.h"


ToonRender::ToonRender()
{
	//深度値出力用のレンダリングターゲットを作成。
	m_toonRenderRT.Create(2048, 2048, DXGI_FORMAT_R32_FLOAT);
}


ToonRender::~ToonRender()
{
}

void ToonRender::Draw()
{
	//トゥーンレンダにレンダリング
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

	//トゥーンレンダにレンダリング
	ZPrepass();

	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);

	oldRenderTargetView->Release();
	oldDepthStencilView->Release();
}

void ToonRender::ZPrepass()
{
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	//レンダリングターゲットを切り替える

	ID3D11RenderTargetView* rts[] = {
		m_toonRenderRT.GetRenderTargetView()
	};
	d3dDeviceContext->OMSetRenderTargets(1, rts, m_toonRenderRT.GetDepthStensilView());


	//ビューポートを設定
	d3dDeviceContext->RSSetViewports(1, m_toonRenderRT.GetViewport());
	//トゥーンレンダーをクリア
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_toonRenderRT.ClearRenderTarget(clearColor);

	//トゥーンレンダにレンダリング。
	for (auto& toonRender : m_toonRender) {
		toonRender->Draw(
			enRenderMode_ToonRender,
			g_camera3D.GetViewMatrix(),
			g_camera3D.GetProjectionMatrix()
		);
	}
	m_toonRender.clear();
}
