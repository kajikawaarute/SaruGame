#pragma once
#include "IGameObject.h"
#include "Sprite.h"
#include "RenderTarget.h"

class Player;
class Stage;
class Enemy;
class GameCamera;
class Saru;
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
	Saru* m_saru = nullptr;						//�T���N���X�̃C���X�^���X
	RenderTarget m_mainRenderTarget;			//���C�������_�����O�^�[�Q�b�g
	Sprite m_copyMainRtToFrameBufferSprite;		//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
};

