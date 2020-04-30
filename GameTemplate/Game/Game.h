#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "DirectXTK/Inc/SpriteBatch.h"

class Player;
class Stage;
class Enemy;
class GameCamera;
class Saru;
class Title;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
private:
	CSoundEngine m_soundEnigne;					//�T�E���h�G���W��
	prefab::CSoundSource m_gameBGM;				//�Q�[����BGM

	Player* m_pl = nullptr;						//�v���C���[�̃C���X�^���X
	Stage* m_stage = nullptr;					//�X�e�[�W�̃C���X�^���X
	Enemy* m_ene[2] = { nullptr, nullptr};						//�G�l�~�[�̃C���X�^���X
	GameCamera* m_gCamera = nullptr;			//�Q�[���J�����̃C���X�^���X
	Saru* m_saru[2] = {nullptr, nullptr};		//�T���N���X�̃C���X�^���X
};

