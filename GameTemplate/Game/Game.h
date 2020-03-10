#pragma once
#include "IGameObject.h"
#include "Sprite.h"
#include "RenderTarget.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "DirectXTK/Inc/SpriteBatch.h"

class Player;
class Stage;
class Enemy;
class GameCamera;
class Saru;
class BananaPeel;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
private:
	CSoundEngine m_soundEnigne;					//�T�E���h�G���W��
	CSoundSource m_gameBGM;						//�Q�[����BGM

	//ID3D11Device* m_device;									//�\�z�ς�
	//ID3D11DeviceContext* m_deviceContext;					//�\�z�ς�
	//std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;	//�X�v���C�g�o�b�`
	//ID3D11ShaderResourceView* m_shaderResourceView;			//�ǂݍ��񂾉摜�t�@�C���̕ۑ���

	Player* m_pl = nullptr;						//�v���C���[�̃C���X�^���X
	Stage* m_stage = nullptr;					//�X�e�[�W�̃C���X�^���X
	Enemy* m_ene = nullptr;						//�G�l�~�[�̃C���X�^���X
	GameCamera* m_gCamera = nullptr;			//�Q�[���J�����̃C���X�^���X
	Saru* m_saru[2] = {nullptr, nullptr};		//�T���N���X�̃C���X�^���X

	BananaPeel* m_banaPeel = nullptr;
};

