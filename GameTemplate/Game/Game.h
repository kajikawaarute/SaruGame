#pragma once
#include "IGameObject.h"
#include "Sprite.h"
#include "RenderTarget.h"

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
	Player* m_pl = nullptr;						//�v���C���[�̃C���X�^���X
	Stage* m_stage = nullptr;					//�X�e�[�W�̃C���X�^���X
	Enemy* m_ene = nullptr;						//�G�l�~�[�̃C���X�^���X
	GameCamera* m_gCamera = nullptr;			//�Q�[���J�����̃C���X�^���X
	Saru* m_saru[2] = {nullptr, nullptr};		//�T���N���X�̃C���X�^���X
	BananaPeel* m_banana = nullptr;				//�o�i�i�̔�̃C���X�^���X
};

