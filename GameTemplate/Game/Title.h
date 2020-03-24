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
private:
	ID3D11Device* m_device;									//�\�z�ς�
	ID3D11DeviceContext* m_deviceContext;					//�\�z�ς�
	DirectX::SpriteBatch* m_spriteBatch;					//�X�v���C�g�o�b�`
	ID3D11ShaderResourceView* m_shaderResourceView;			//�ǂݍ��񂾉摜�t�@�C���̕ۑ���

	Game* m_game = nullptr;
};

