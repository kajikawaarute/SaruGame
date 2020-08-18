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
		//�V���h�E�}�b�v�p��SRV��ݒ�B(t2)
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_ShadowMap, 1, &shadowMapSRV);
		//�g�D�[�������_�p��SRV��ݒ�B(t3)
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_ToonRender, 1, &toonRenderSRV);
	}break;
	case enRenderMode_CreateShadowMap:
		//�V���h�E�}�b�v�����p�̃V�F�[�_�[��ݒ�B
		//�V���h�E�}�b�v�����B
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	case enRenderMode_ToonRender:
		//�g�D�[�������_�[�p�̃V�F�[�_�[��ݒ�B
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsToonRender.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psToonRender.GetBody(), NULL, 0);
		break;
	}

}