#include "stdafx.h"
#include "GameOver.h"
#include "Fade.h"

const float GAMEOVER_POSITION_Y = 100.0f;		//�Q�[���I�[�o�[�̕�������������WY
const float GAMEOVER_MOVE_SPEED = 10.0f;	//�Q�[���I�[�o�[�̕����������鑬�x�B

GameOver::GameOver()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_device = g_graphicsEngine->GetDevice();

	//�摜�̓ǂݍ���
	DirectX::CreateDDSTextureFromFile(
		m_device,
		L"Assets/sprite/GAMEOVER.dds",
		nullptr,
		&m_shaderResourceView
	);
}

GameOver::~GameOver()
{
	g_goMgr.DeleteGO(m_fade);
}

void GameOver::Update()
{
	//�Q�[���I�[�o�[�̕�����������B
	if (m_positionY < GAMEOVER_POSITION_Y)
	{
		m_positionY += GAMEOVER_MOVE_SPEED;
	}
	else if (m_fadeFlag == false) {
		m_fade = g_goMgr.NewGO<Fade>();
		m_fadeFlag = true;
	}
	else {
		//�t�F�[�h�A�E�g
		m_fade->StartFadeOut();
	}
}

void GameOver::Draw()
{
	SpriteBatchDraw();
}

void GameOver::SpriteBatchDraw()
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(
		m_shaderResourceView,							//�ǂݍ��񂾉摜�t�@�C��
		DirectX::XMFLOAT2(m_positionX, m_positionY),	//�摜�̍��W
		nullptr,										//�X�v���C�g��C�ӂ̗̈�ɕ\��
		color,											//�J���[
		m_rotation,										//��]�p�x
		DirectX::XMFLOAT2(0.0f, 0.0f),					//��]���̈ʒu
		m_scale,										//�g�嗦
		DirectX::SpriteEffects::SpriteEffects_None,		//�X�v���C�g�̕\�����]
		m_depth											//�X�v���C�g�̐[�x���w��
	);
	m_spriteBatch->End();
}
