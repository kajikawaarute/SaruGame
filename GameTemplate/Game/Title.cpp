#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Fade.h"

const float TITLE_POSITION_X = 50.0f;	//�^�C�g�������̍��WX
const float TITLE_POSITION_Y = 10.0f;	//�^�C�g�������̍��WY
const int TITLE_GAME_START_TIME = 60;	//�Q�[�����J�n����^�C��

Title::Title()
{
	m_spriteBatch = GetSpriteBatchGraphicsEngine();

	for (int i = 0; i < EnSpriteNum; i++)
	{
		m_device[i] = GetD3DDeviceGraphicsEngine();
	}

	//�^�C�g���摜�̓ǂݍ���
	DirectX::CreateDDSTextureFromFile(
		m_device[EnSprite_title],							//�f�o�C�X
		L"Assets/sprite/Title.dds",				//�ǂݍ��މ摜�t�@�C��
		nullptr,
		&m_shaderResourceView[EnSprite_title]				//�ǂݍ��񂾃t�@�C���̏����i�[
	);

	//�^�C�g�����̉摜�̓ǂݍ���
	DirectX::CreateDDSTextureFromFile(
		m_device[EnSprite_Catch_the_monkey],							//�f�o�C�X
		L"Assets/sprite/Catch_the_monkey.dds",	//�ǂݍ��މ摜�t�@�C��
		nullptr,
		&m_shaderResourceView[EnSprite_Catch_the_monkey]				//�ǂݍ��񂾃t�@�C���̏����i�[
	);
	m_positionX[EnSprite_Catch_the_monkey] = -1500.0f;

	//Press_Start_Button�̉摜�̓ǂݍ���
	DirectX::CreateDDSTextureFromFile(
		m_device[EnSprite_Press_Start],							//�f�o�C�X
		L"Assets/sprite/Press_Start.dds",		//�ǂݍ��މ摜�t�@�C��
		nullptr,
		&m_shaderResourceView[EnSprite_Press_Start]				//�ǂݍ��񂾃t�@�C���̏����i�[
	);
	m_positionY[EnSprite_Press_Start] = 300.0f;
}


Title::~Title()
{
	DeleteGO(m_fade);
}

void Title::Update()
{
	if (g_pad[0].IsTrigger(enButtonStart) && m_startFlag == false && m_positionX[EnSprite_Catch_the_monkey] == 0.0f && m_positionY[EnSprite_Press_Start] == 0.0f)
	{
		m_fade = NewGO<Fade>();
		m_startFlag = true;
	}
	if (m_startFlag == true) {
		m_gameStartTimer++;
		m_fade->StartFadeOut();
		if (m_gameStartTimer > TITLE_GAME_START_TIME) {
			Game::stageNo = eStage_1;
			m_game = NewGO<Game>();
			DeleteGO(this);
		}
	}
	if (m_positionX[EnSprite_Catch_the_monkey] < 0.0f) {
		m_positionX[EnSprite_Catch_the_monkey] += TITLE_POSITION_X;
	}
	if (m_positionY[EnSprite_Press_Start] > 0.0f) {
		m_positionY[EnSprite_Press_Start] -= TITLE_POSITION_Y;
	}
	
}

void Title::Draw()
{
	SpriteBatchDraw();
}

void Title::SpriteBatchDraw()
{
	for (int i = 0; i < EnSpriteNum; i++)
	{
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
