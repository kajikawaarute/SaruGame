#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "level/Level.h"

class Player;
class Saru;
class Player;
class Enemy;
class JumpFloor;

class Stage;
class Stage2;
class GameCamera;
class Title;
class PlayerHP;
class GameClear;
class GameOver;
class ButtonUI;
class Game : public IGameObject
{
public:
	static int stageNo;	//�X�e�[�W�ԍ�
	Game();
	~Game();
	void Update();
	void Draw();
private:
	prefab::CSoundSource m_gameBGM;				//�Q�[����BGM

	Player* m_pl = nullptr;						//�v���C���[�̃C���X�^���X
	Stage* m_stage = nullptr;					//�X�e�[�W�̃C���X�^���X
	Stage2* m_stage2 = nullptr;					//�X�e�[�W2�̃C���X�^���X

	GameCamera* m_gCamera = nullptr;			//�Q�[���J�����̃C���X�^���X
	PlayerHP* m_playerHP = nullptr;				//�v���C���[HP�̃C���X�^���X
	GameClear* m_gameClear = nullptr;			//�Q�[���N���A�̃C���X�^���X
	GameOver* m_gameOver = nullptr;				//�Q�[���I�[�o�[�̃C���X�^���X
	ButtonUI* m_buttonUI = nullptr;

	Enemy* m_enemy[6] = { nullptr };		//�G�l�~�[�̃C���X�^���X
	Saru* m_saru[3] = { nullptr };			//�T���N���X�̃C���X�^���X
	JumpFloor* m_jumpFloor = nullptr;		//�W�����v���̃C���X�^���X

	std::vector<Saru*> m_sarus;				//�T���̃��X�g
	std::vector<Enemy*> m_enemys;			//�G�l�~�[�̃��X�g

	Level m_level;		//���x���̃C���X�^���X

	int m_gameClearTimer = 0;		//�Q�[���N���A�܂ł̃^�C�}�[
	int m_gameOverTimer = 0;		//�Q�[���I�[�o�[�܂ł̃^�C�}�[
};

