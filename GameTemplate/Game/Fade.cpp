#include "stdafx.h"
#include "Fade.h"
#include "IGameObjectManager.h"

Fade::Fade()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_device = g_graphicsEngine->GetDevice();

	//�摜�̓ǂݍ��݁B
	DirectX::CreateDDSTextureFromFile(
		m_device,							//�f�o�C�X
		L"Assets/sprite/Fade.dds",		//�ǂݍ��މ摜�t�@�C��
		nullptr,
		&m_shaderResourceView				//�ǂݍ��񂾃t�@�C���̏����i�[
	);
}


Fade::~Fade()
{
}

void Fade::Update()
{
	switch (m_state) {
	case enState_FadeIn:	//�t�F�[�h�C��
		m_alpha -= m_alphaIncAmount;
		if (m_alpha <= 0.0f)
		{
			m_alpha = 0.0f;
		}
		break;
	case enState_FadeOut:	//�t�F�[�h�A�E�g
		m_alpha += m_alphaIncAmount;
		if (m_alpha >= 1.0f)
		{
			m_alpha = 1.0f;
		}
		break;
	case enState_Idle:

		break;
	}
}

void Fade::Draw()
{
	SpriteBatctDraw();
}

void Fade::SpriteBatctDraw()
{

	DirectX::FXMVECTOR m_alphaColor = { 0.0f, 0.0f, 0.0f, m_alpha };		//�J���[�B

	m_spriteBatch->Begin();
	m_spriteBatch->Draw(
		m_shaderResourceView,							//�ǂݍ��񂾉摜�t�@�C��
		DirectX::XMFLOAT2(m_positionX, m_positionY),	//�摜�̍��W
		nullptr,										//�X�v���C�g��C�ӂ̗̈�ɕ\��
		m_alphaColor,									//�J���[
		m_rotation,										//��]�p�x
		DirectX::XMFLOAT2(0.0f, 0.0f),					//��]���̈ʒu
		m_scale,										//�g�嗦
		DirectX::SpriteEffects::SpriteEffects_None,		//�X�v���C�g�̕\�����]
		m_depth											//�X�v���C�g�̐[�x���w��
	);
	m_spriteBatch->End();
}
