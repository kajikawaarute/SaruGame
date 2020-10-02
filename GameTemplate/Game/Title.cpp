#include "stdafx.h"
#include "Title.h"
#include "IGameObjectManager.h"
#include "Game.h"
#include "Fade.h"

const float TITLE_POSITION_X = 50.0f;	//�^�C�g�������̍��WX
const float TITLE_POSITION_Y = 10.0f;	//�^�C�g�������̍��WY
const int TITLE_GAME_START_TIME = 60;	//�Q�[�����J�n����^�C��

Title::Title()
{
	m_spriteBatch = g_graphicsEngine->GetSpriteBatch();

	for (int i = 0; i < 3; i++)
	{
		m_device[i] = g_graphicsEngine->GetDevice();
	}

	//�^�C�g���摜�̓ǂݍ���
	DirectX::CreateDDSTextureFromFile(
		m_device[0],							//�f�o�C�X
		L"Assets/sprite/Title.dds",				//�ǂݍ��މ摜�t�@�C��
		nullptr,
		&m_shaderResourceView[0]				//�ǂݍ��񂾃t�@�C���̏����i�[
	);

	//�^�C�g�����̉摜�̓ǂݍ���
	DirectX::CreateDDSTextureFromFile(
		m_device[1],							//�f�o�C�X
		L"Assets/sprite/Catch_the_monkey.dds",	//�ǂݍ��މ摜�t�@�C��
		nullptr,
		&m_shaderResourceView[1]				//�ǂݍ��񂾃t�@�C���̏����i�[
	);
	m_positionX[1] = -1500.0f;

	//Press_Start_Button�̉摜�̓ǂݍ���
	DirectX::CreateDDSTextureFromFile(
		m_device[2],							//�f�o�C�X
		L"Assets/sprite/Press_Start.dds",		//�ǂݍ��މ摜�t�@�C��
		nullptr,
		&m_shaderResourceView[2]				//�ǂݍ��񂾃t�@�C���̏����i�[
	);
	m_positionY[2] = 300.0f;
}


Title::~Title()
{
	g_goMgr.DeleteGO(m_fade);
}

void Title::Update()
{
	if (g_pad[0].IsTrigger(enButtonStart) && m_startFlag == false && m_positionX[1] == 0.0f && m_positionY[2] == 0.0f)
	{
		m_fade = g_goMgr.NewGO<Fade>();
		m_startFlag = true;
	}
	if (m_startFlag == true) {
		m_gameStartTimer++;
		m_fade->StartFadeOut();
		if (m_gameStartTimer > TITLE_GAME_START_TIME) {
			Game::stageNo = 0;
			m_game = g_goMgr.NewGO<Game>();
			g_goMgr.DeleteGO(this);
		}
	}
	if (m_positionX[1] < 0.0f) {
		m_positionX[1] += TITLE_POSITION_X;
	}
	if (m_positionY[2] > 0.0f) {
		m_positionY[2] -= TITLE_POSITION_Y;
	}
	
}

void Title::Draw()
{
	SpriteBatchDraw();
}

void Title::SpriteBatchDraw()
{
	for (int i = 0; i < 3; i++)
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
