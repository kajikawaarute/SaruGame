#pragma once
#include "IGameObject.h"
#include "physics/PhysicsStaticObject.h"
#include "level/Level.h"

class Saru;
class Player;
class Enemy;
class JumpFloor;
class Stage : public IGameObject
{
public:
	Stage();
	~Stage();
	void Update();
	void Draw();

	Player* GetPlayer()
	{
		return m_pl;
	}
private:
	Level m_level;

	Player* m_pl = nullptr;																//�v���C���[�̃C���X�^���X
	Enemy* m_enemy[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };		//�G�l�~�[�̃C���X�^���X
	Saru* m_saru[3] = { nullptr, nullptr , nullptr };									//�T���N���X�̃C���X�^���X
	JumpFloor* m_jumpFloor = nullptr;													//�W�����v���̃C���X�^���X

	std::vector<Saru*> m_sarus;								//�T���̃��X�g
	std::vector<Enemy*> m_enemys;							//�G�l�~�[�̃��X�g
};

