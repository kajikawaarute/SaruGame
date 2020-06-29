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

	//���C�g�̕������v�Z����B
	auto lightDir = m_lightCameraTarget - m_lightCameraPosition;
	if (lightDir.Length() < 0.0001f) {
		//���C�g�J�����̒����_�Ǝ��_���߂�
		std::abort();
	}
	lightDir.Normalize();
	//���C�g�̕����ɂ���āA���C�g�J�����̏���������߂�B
	CVector3 lightCameraUpAxis;
	if (fabsf(lightDir.y) > 0.99998f) {
		lightCameraUpAxis = CVector3::AxisX();
	}
	else {
		lightCameraUpAxis = CVector3::AxisY();
	}
	//���C�g�r���[�s����v�Z
	m_lightViewMatrix.MakeLookAt(
		m_lightCameraPosition,
		m_lightCameraTarget,
		lightCameraUpAxis
	);
	//���C�g�v���W�F�N�V�����s����쐬
	m_lightProjMatrix.MakeOrthoProjectionMatrix(
		3000,
		3000,
		0.1f,
		5000.0f
	);
}

void ShadowMap::Draw()
{
	//�V���h�E�}�b�v�Ƀ����_�����O
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

	//�V���h�E�}�b�v�Ƀ����_�����O
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
	
	//�����_�����O�^�[�Q�b�g��؂�ւ���

	ID3D11RenderTargetView* rts[] = {
		m_shadowMapRT.GetRenderTargetView()
	};
	d3dDeviceContext->OMSetRenderTargets(1, rts, m_shadowMapRT.GetDepthStensilView());

	
	//�r���[�|�[�g��ݒ�
	d3dDeviceContext->RSSetViewports(1, m_shadowMapRT.GetViewport());
	//�V���h�E�}�b�v���N���A
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_shadowMapRT.ClearRenderTarget(clearColor);

	//�V���h�E�L���X�^�[���V���h�E�}�b�v�Ƀ����_�����O�B
	for (auto& caster : m_shadowCasters) {
		caster->Draw(
			enRenderMode_CreateShadowMap,
			m_lightViewMatrix,
			m_lightProjMatrix
		);
	}
	m_shadowCasters.clear();
}
