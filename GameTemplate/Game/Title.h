#pragma once
#include "IGameObject.h"

class Game;
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
	DirectX::SpriteBatch* m_spriteBatch;					//�X�v���C�g�o�b�`

	ID3D11Device* m_device[3];									//�\�z�ς�
	ID3D11DeviceContext* m_deviceContext[3];					//�\�z�ς�
	ID3D11ShaderResourceView* m_shaderResourceView[3];			//�ǂݍ��񂾉摜�t�@�C���̕ۑ���

	float m_positionX[3] = {0.0f, 0.0f, 0.0f};			//�摜��X���W
	float m_positionY[3] = {0.0f, 0.0f, 0.0f};			//�摜��Y���W

	Game* m_game = nullptr;				//�Q�[���̃C���X�^���X
};

