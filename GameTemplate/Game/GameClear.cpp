#include "stdafx.h"
#include "GameClear.h"
#include "IGameObjectManager.h"

const float GAMECLEAR_POSITION_Y = 100.0f;		//�Q�[���I�[�o�[�̕�������������WY
const float GAMECLEAR_MOVE_SPEED = 10.0f;	//�Q�[���I�[�o�[�̕����������鑬�x�B

GameClear::GameClear()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	m_device = g_graphicsEngine->GetDevice();

	//�摜�̓ǂݍ��݁B
	DirectX::CreateDDSTextureFromFile(
		m_device,
		L"Assets/sprite/GAMECLEAR.dds",
		nullptr,
		&m_shaderResourceView
	);
}

GameClear::~GameClear()
{
}

void GameClear::Update()
{
	//�Q�[���N���A�̕�����������B
	if (m_positionY < GAMECLEAR_POSITION_Y)
	{
		m_positionY += GAMECLEAR_MOVE_SPEED;
	}
}

void GameClear::Draw()
{
	SpriteBatchDraw();
}

void GameClear::SpriteBatchDraw()
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
