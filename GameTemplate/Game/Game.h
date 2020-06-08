#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Player;
class Stage;
class GameCamera;
class Title;
class PlayerHP;
class GameClear;
class GameOver;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
private:
	prefab::CSoundSource m_gameBGM;				//�Q�[����BGM

	Player* m_pl = nullptr;						//�v���C���[�̃C���X�^���X
	Stage* m_stage = nullptr;					//�X�e�[�W�̃C���X�^���X
	GameCamera* m_gCamera = nullptr;			//�Q�[���J�����̃C���X�^���X
	PlayerHP* m_playerHP = nullptr;				//�v���C���[HP�̃C���X�^���X
	GameClear* m_gameClear = nullptr;			//�Q�[���N���A�̃C���X�^���X
	GameOver* m_gameOver = nullptr;				//�Q�[���I�[�o�[�̃C���X�^���X

	int m_gameClearTimer = 0;					//�Q�[���N���A�܂ł̃^�C�}�[
};

