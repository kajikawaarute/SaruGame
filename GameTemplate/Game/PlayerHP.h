#pragma once
#include "IGameObject.h"

class PlayerHP : public IGameObject
{
public:
	PlayerHP();
	~PlayerHP();

	/// <summary>
	/// �v���C���[HP�̍X�V�֐�
	/// </summary>
	void Update();

	/// <summary>
	/// �v���C���[HP�̕`��֐�
	/// </summary>
	void Draw();

	/// <summary>
	/// �_���[�W�t���O��ݒ�
	/// </summary>
	/// <param name="flag"></param>
	/// <returns></returns>
	bool SetDamageFlag(bool flag)
	{
		return m_damageFlag = flag;
	}

	/// <summary>
	/// �Q�[���I�[�o�[�t���O���擾
	/// </summary>
	/// <returns></returns>
	bool GetGameOver()
	{
		return m_gameOverFlag;
	}
	/// <summary>
	/// �X�v���C�g�o�b�`�̕`��֐�
	/// </summary>
	void SpriteBatchDraw();
private:
	const int m_playerHP = 3;

	DirectX::SpriteBatch* m_spriteBatch;					//�X�v���C�g�o�b�`
	DirectX::FXMVECTOR color = DirectX::Colors::White;		//�J���[�B

	ID3D11Device* m_device[3];									//�\�z�ς�
	ID3D11DeviceContext* m_deviceContext[3];					//�\�z�ς�
	ID3D11ShaderResourceView* m_shaderResourceView[3];			//�ǂݍ��񂾉摜�t�@�C���̕ۑ���

	float m_positionX[3] = { 0.0f, 50.0f, 100.0f};		//X���W
	float m_positionY[3] = { 0.0f, 0.0f, 0.0f};			//Y���W
	float m_rotation[3] = {0.0f, 0.0f, 0.0f};			//�摜�̉�]
	float m_scale[3] = { 0.1f, 0.1f, 0.1f};				//�g�嗦
	float m_depth[3] = { 0.0f, 0.0f, 0.0f};				//�X�v���C�g�̐[�x

	bool m_damageFlag = false;		//�U�����󂯂����̔���t���O
	bool m_muteki = false;			//���G����
	bool m_gameOverFlag = false;	//�Q�[���I�[�o�[�t���O
	int m_mutekiTimer = 0;			//���G����
};

