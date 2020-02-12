#pragma once
#include "IGameObject.h"
#include "Sprite.h"
#include "RenderTarget.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

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
	/// <summary>
	/// Effekser�̏�����
	/// </summary>
	void InitEffekseer();
private:
	CSoundEngine m_soundEnigne;					//�T�E���h�G���W��
	CSoundSource m_gameBGM;						//�Q�[����BGM

	//Effekseer�}�l�[�W���[�Ǘ�
	Effekseer::Manager* m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;

	Effekseer::Effect* m_effekt = nullptr;		//�G�t�F�N�g
	Effekseer::Handle m_playEffectHandle = -1;
	Player* m_pl = nullptr;						//�v���C���[�̃C���X�^���X
	Stage* m_stage = nullptr;					//�X�e�[�W�̃C���X�^���X
	Enemy* m_ene = nullptr;						//�G�l�~�[�̃C���X�^���X
	GameCamera* m_gCamera = nullptr;			//�Q�[���J�����̃C���X�^���X
	Saru* m_saru[2] = {nullptr, nullptr};		//�T���N���X�̃C���X�^���X
	BananaPeel* m_banana = nullptr;				//�o�i�i�̔�̃C���X�^���X
};

