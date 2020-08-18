#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"
#include "ShadowMap.h"
#include "ToonRender.h"

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	switch (m_renderMode)
	{
	case enRenderMode_Normal: {
		deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);
		auto shadowMapSRV = ShadowMap::GetInstance().GetShadowMapSRV();
		auto toonRenderSRV = ToonRender::GetInstance().GetToonRenderSRV();
		//シャドウマップ用のSRVを設定。(t2)
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_ShadowMap, 1, &shadowMapSRV);
		//トゥーンレンダ用のSRVを設定。(t3)
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_ToonRender, 1, &toonRenderSRV);
	}break;
	case enRenderMode_CreateShadowMap:
		//シャドウマップ生成用のシェーダーを設定。
		//シャドウマップ生成。
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	case enRenderMode_ToonRender:
		//トゥーンレンダー用のシェーダーを設定。
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsToonRender.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psToonRender.GetBody(), NULL, 0);
		break;
	}

}