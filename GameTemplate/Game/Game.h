#pragma once
#include "IGameObject.h"


class Player;
class Stage;
class Enemy;
class GameCamera;
class GetAmi;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	void Update();
	void Draw();
private:
	Player* m_pl = nullptr;		//�v���C���[�̃C���X�^���X
	Stage* m_stage = nullptr;		//�X�e�[�W�̃C���X�^���X
	Enemy* m_ene = nullptr;		//�G�l�~�[�̃C���X�^���X
	GameCamera* m_gCamera = nullptr; //�Q�[���J�����̃C���X�^���X
	
};

