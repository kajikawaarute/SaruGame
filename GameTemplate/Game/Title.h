#pragma once
#include "IGameObject.h"

class Game;
class Fade;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	/// <summary>
	/// �^�C�g���̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �^�C�g���̕`��֐�
	/// </summary>
	void Draw();

	/// <summary>
	/// spriteBatch�̕`��֐�
	/// </summary>
	void SpriteBatchDraw();
private:
	Game* m_game = nullptr;				//�Q�[���̃C���X�^���X
	Fade* m_fade = nullptr;

	DirectX::SpriteBatch* m_spriteBatch;					//�X�v���C�g�o�b�`
	DirectX::FXMVECTOR color = DirectX::Colors::White;		//�J���[�B

	ID3D11Device* m_device[3];									//�\�z�ς�
	ID3D11DeviceContext* m_deviceContext[3];					//�\�z�ς�
	ID3D11ShaderResourceView* m_shaderResourceView[3];			//�ǂݍ��񂾉摜�t�@�C���̕ۑ���

	float m_positionX[3] = {0.0f, 0.0f, 0.0f};			//�摜��X���W
	float m_positionY[3] = {0.0f, 0.0f, 0.0f};			//�摜��Y���W
	float m_rotation[3] = { 0.0f, 0.0f, 0.0f };			//�摜�̉�]
	float m_scale[3] = { 1.0f, 1.0f, 1.0f };			//�g�嗦
	float m_depth[3] = { 0.0f, 0.0f, 0.0f };			//�X�v���C�g�̐[�x

	int m_gameStartTimer = 0;		//�Q�[�����n�߂�^�C�}�[
	bool m_startFlag = false;		//�Q�[�����n�߂�t���O
};

