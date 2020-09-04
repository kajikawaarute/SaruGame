#include "stdafx.h"
#include "IGameObjectManager.h"
#include "PlayerHP.h"

const float PLAYER_HP_SPRITE_SCALE = 0.005f;	//�v���C���[HP�̊g�嗦
const float PLAYER_HP_SPRITE_SIZE = 0.001f;		//�v���C���[HP�̑傫��

PlayerHP::PlayerHP()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();

	for (int i = 0; i < m_playerHP; i++) {
		//�摜�̓ǂݍ��݁B
		m_device[i] = g_graphicsEngine->GetDevice();
		DirectX::CreateDDSTextureFromFile(
			m_device[i],						//�f�o�C�X
			L"Assets/sprite/PlayerHP.dds",	//�ǂݍ��މ摜
			nullptr,
			&m_shaderResourceView[i]			//�ǂݍ��񂾃t�@�C���̏����i�[
		);
	}
}

PlayerHP::~PlayerHP()
{
}

void PlayerHP::Update()
{
	if (m_muteki) {
		m_mutekiTimer++;
		//���G����
		if (m_mutekiTimer > 30) {
			m_muteki = false;
			m_damageFlag = false;
			m_mutekiTimer = 0;
		}
	}

	if (!m_muteki) {
		if (m_damageFlag && m_scale[2] > PLAYER_HP_SPRITE_SIZE) {
			m_scale[2] -= PLAYER_HP_SPRITE_SCALE;
			if (m_scale[2] < PLAYER_HP_SPRITE_SIZE){
				m_muteki = true;
			}
		}
		else if (m_damageFlag && m_scale[1] > PLAYER_HP_SPRITE_SIZE) {
			m_scale[1] -= PLAYER_HP_SPRITE_SCALE;
			if (m_scale[1] < PLAYER_HP_SPRITE_SIZE) {
				m_muteki = true;
			}
		}
		else if (m_damageFlag && m_scale[0] > PLAYER_HP_SPRITE_SIZE) {
			m_scale[0] -= PLAYER_HP_SPRITE_SCALE;
			if (m_scale[0] < PLAYER_HP_SPRITE_SIZE) {
				m_gameOverFlag = true;
			}
		}
	}
}

void PlayerHP::Draw()
{
	SpriteBatchDraw();
}

void PlayerHP::SpriteBatchDraw()
{
	for (int i = 0; i < m_playerHP; i++) {
		m_spriteBatch->Begin();
		m_spriteBatch->Draw(
			m_shaderResourceView[i],							//�ǂݍ��񂾉摜�t�@�C��
			DirectX::XMFLOAT2(m_positionX[i], m_positionY[i]),	//�摜�̍��W
			nullptr,											//�X�v���C�g��C�ӂ̗̈�ɕ\��
			color,												//�J���[
			m_rotation[i],										//��]�p�x
			DirectX::XMFLOAT2(0.0f, 0.0f),						//��]���̈ʒu
			m_scale[i],											//�g�嗦
			DirectX::SpriteEffects::SpriteEffects_None,			//�X�v���C�g�̕\�����]
			m_depth[i]											//�X�v���C�g�̐[�x���w��
		);
		m_spriteBatch->End();
	}
}
