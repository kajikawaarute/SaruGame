#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "level/Level.h"

class Player;
class Saru;
class Enemy;
class GunEnemy;
class JumpFloor;
class Wall;
class Sky;

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

	/// <summary>
	/// �Q�[���̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �Q�[���̕`��֐�
	/// </summary>
	void Draw();
private:
	enum { MAX_SARU = 100 };				//1�X�e�[�W�̃T���̍ő吔�B
	prefab::CSoundSource m_gameBGM;			//�X�e�[�W1��BGM
	prefab::CSoundSource m_gameBGM2;		//�X�e�[�W2��BGM

	Player* m_pl = nullptr;					//�v���C���[�̃C���X�^���X

	Stage* m_stage = nullptr;				//�X�e�[�W�̃C���X�^���X
	Stage2* m_stage2 = nullptr;				//�X�e�[�W2�̃C���X�^���X
	JumpFloor* m_jumpFloor = nullptr;		//�W�����v���̃C���X�^���X
	Wall* m_wall = nullptr;					//�X�e�[�W�ǂ̃C���X�^���X
	Sky* m_sky = nullptr;					//��̃C���X�^���X

	GameCamera* m_gCamera = nullptr;		//�Q�[���J�����̃C���X�^���X

	PlayerHP* m_playerHP = nullptr;			//�v���C���[HP�̃C���X�^���X
	GameClear* m_gameClear = nullptr;		//�Q�[���N���A�̃C���X�^���X
	GameOver* m_gameOver = nullptr;			//�Q�[���I�[�o�[�̃C���X�^���X
	ButtonUI* m_buttonUI = nullptr;			//�{�^��UI�̃C���X�^���X

	int m_saruNo = 0;						//�T���̐�
	Saru* m_sarus[MAX_SARU] = {nullptr};	//�T���̃��X�g
	std::vector<Enemy*> m_enemys;			//�G�l�~�[�̃��X�g
	std::vector<GunEnemy*> m_gunEnemys;		//�K���G�l�~�[�̃��X�g

	Level m_level;		//���x���̃C���X�^���X

	int m_gameClearTimer = 0;		//�Q�[���N���A�܂ł̃^�C�}�[
	int m_gameOverTimer = 0;		//�Q�[���I�[�o�[�܂ł̃^�C�}�[
};

