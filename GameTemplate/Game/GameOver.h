#pragma once
#include "IGameObject.h"

class Fade;
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();

	/// <summary>
	/// �Q�[���I�[�o�[�̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �Q�[���I�[�o�[�̕`��֐�
	/// </summary>
	void Draw();

	/// <summary>
	/// SpriteBatch�̕`��֐�
	/// </summary>
	void SpriteBatchDraw();
private:
	DirectX::SpriteBatch* m_spriteBatch;					//�X�v���C�g�o�b�`
	DirectX::FXMVECTOR color = DirectX::Colors::White;		//�J���[�B

	ID3D11Device* m_device;									//�\�z�ς�
	ID3D11DeviceContext* m_deviceContext;					//�\�z�ς�
	ID3D11ShaderResourceView* m_shaderResourceView;			//�ǂݍ��񂾉摜�t�@�C���̕ۑ���

	float m_positionX = 300.0f;			//�摜��X���W
	float m_positionY = -200.0f;		//�摜��Y���W
	float m_rotation = 0.0f;			//�摜�̉�]
	float m_scale = 0.5f;				//�g�嗦
	float m_depth = 0.0f;				//�X�v���C�g�̐[�x

	Fade* m_fade = nullptr;				//�t�F�[�h�̃C���X�^���X

	bool m_fadeFlag = false;			//�t�F�[�h���s�����̃t���O
};

