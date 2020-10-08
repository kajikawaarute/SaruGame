#pragma once

class Fade : public IGameObject
{
public:
	Fade();
	~Fade();

	/// <summary>
	/// �t�F�[�h�̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �t�F�[�h�̕`��֐�
	/// </summary>
	void Draw();

	/// <summary>
	///  SpriteBatct�̕`��֐��B
	/// </summary>
	void SpriteBatctDraw();

	/// <summary>
	/// �t�F�[�h�C��
	/// </summary>
	void StartFadeIn()
	{
		m_state = enState_FadeIn;
	}
	/// <summary>
	/// �t�F�[�h�A�E�g
	/// </summary>
	void StartFadeOut()
	{
		m_state = enState_FadeOut;
	}

private:
	DirectX::SpriteBatch* m_spriteBatch;					//�X�v���C�g�o�b�`

	ID3D11Device* m_device;									//�\�z�ς�
	ID3D11DeviceContext* m_deviceContext;					//�\�z�ς�
	ID3D11ShaderResourceView* m_shaderResourceView;			//�ǂݍ��񂾉摜�t�@�C���̕ۑ���

	float m_positionX = 0.0f;		//�摜��X���W
	float m_positionY = 0.0f;		//�摜��Y���W
	float m_rotation = 0.0f;		//�摜�̉�]
	float m_scale = 2.5f;			//�g�嗦
	float m_depth = 0.0f;			//�X�v���C�g�̐[�x

	enum EnState {
		enState_FadeIn,		//�t�F�[�h�C�����B
		enState_FadeOut,	//�t�F�[�h�A�E�g���B
		enState_Idle,		//�A�C�h�����B
	};
	EnState m_state = enState_Idle;	//���

	float m_alpha = 0.0f;				//�A���t�@�l
	float m_alphaIncAmount = 0.06f;		//�A���t�@�l�̗�
};

