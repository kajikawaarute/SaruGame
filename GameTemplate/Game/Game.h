#pragma once
#include "IGameObject.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "level/Level.h"

class Player;
class Stage;
class Enemy;
class GameCamera;
class Saru;
class Title;
class PlayerHP;
class GameClear;
class JumpFloor;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
private:
	prefab::CSoundSource m_gameBGM;									//�Q�[����BGM

	Player* m_pl = nullptr;																//�v���C���[�̃C���X�^���X
	//Stage* m_stage = nullptr;															//�X�e�[�W�̃C���X�^���X
	Enemy* m_enemy[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};		//�G�l�~�[�̃C���X�^���X
	GameCamera* m_gCamera = nullptr;													//�Q�[���J�����̃C���X�^���X
	Saru* m_saru[3] = { nullptr, nullptr , nullptr};									//�T���N���X�̃C���X�^���X
	PlayerHP* m_playerHP = nullptr;														//�v���C���[HP�̃C���X�^���X
	GameClear* m_gameClear = nullptr;													//�Q�[���N���A�̃C���X�^���X
	JumpFloor* m_jumpFloor = nullptr;													//�W�����v���̃C���X�^���X

	std::vector<Saru*> m_sarus;								//�T���̃��X�g
	std::vector<Enemy*> m_enemys;							//�G�l�~�[�̃��X�g

	Level level;
};

