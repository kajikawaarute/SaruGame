#pragma once

/// <summary>
/// �����_�����O���[�h�B
/// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//�s���ȃ����_�����O���[�h�B
	enRenderMode_CreateShadowMap,	//�V���h�E�}�b�v�����B
	enRenderMode_ToonRender,		//�g�D�[�������_�[
	enRenderMode_Normal,			//�ʏ탌���_�����O�B
	enRenderMode_Num,				//�����_�����O���[�h�̐��B
};

/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */
class GraphicsEngine
{
private:
	GraphicsEngine();
	~GraphicsEngine();

public:
	/// <summary>
	/// �O���t�B�b�N�X�G���W���̃C���X�^���X���擾�B
	/// </summary>
	/// <returns>�O���t�B�b�N�X�G���W���̃C���X�^���X</returns>
	static GraphicsEngine* GetInstance()
	{
		static GraphicsEngine* instance = nullptr;
		if (instance == nullptr) {
			instance = new GraphicsEngine();
		}
		return instance;
	}

	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	����B
	 */
	void Release();
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}

	/// <summary>
	/// �f�v�X�X�e���V���r���[���擾�B
	/// </summary>
	/// <returns>�f�v�X�X�e���V���r���[</returns>
	ID3D11DepthStencilView* GetDepthStencilView()
	{
		return m_depthStencilView;
	}

	/// <summary>
	/// �X�v���C�g�o�b�`���擾�B
	/// </summary>
	/// <returns></returns>
	DirectX::SpriteBatch* GetSpriteBatch()
	{
		return m_spriteBatch.get();
	}
	/// <summary>
	/// �X�v���C�g�t�H���g���擾
	/// </summary>
	/// <returns></returns>
	DirectX::SpriteFont* GetSpriteFont()
	{
		return m_spriteFont.get();
	}
	/// <summary>
	/// D3D11�f�o�C�X���擾
	/// </summary>
	/// <returns></returns>
	ID3D11Device* GetDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();
	/*!
	 *@brief	�`��I���B
	 */
	void EndRender();
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11�f�o�C�X�B
	IDXGISwapChain*			m_pSwapChain = NULL;		//�X���b�v�`�F�C���B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11�f�o�C�X�R���e�L�X�g�B
	ID3D11RenderTargetView* m_backBuffer = NULL;		//�o�b�N�o�b�t�@�B
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//���X�^���C�U�X�e�[�g�B
	ID3D11Texture2D*		m_depthStencil = NULL;		//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//�f�v�X�X�e���V���r���[�B

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;	//�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;		//�X�v���C�g�t�H���g

};

//�w���p�[�֐�

/// <summary>
/// D3D11�f�o�C�X���擾�B
/// </summary>
/// <returns>D3D11�f�o�C�X</returns>
static inline ID3D11Device* GetD3DDeviceGraphicsEngine()
{
	return GraphicsEngine::GetInstance()->GetD3DDevice();
}

/// <summary>
/// D3D11�f�o�C�X�R���e�L�X�g���擾�B
/// </summary>
/// <returns>D3D11�f�o�C�X�R���e�L�X�g</returns>
static inline ID3D11DeviceContext* GetD3DDeviceContextGraphicsEngine()
{
	return GraphicsEngine::GetInstance()->GetD3DDeviceContext();
}

/// <summary>
/// �X�v���C�g�o�b�`���擾�B
/// </summary>
/// <returns>�X�v���C�g�o�b�`</returns>
static inline DirectX::SpriteBatch* GetSpriteBatchGraphicsEngine()
{
	return GraphicsEngine::GetInstance()->GetSpriteBatch();
}

/// <summary>
/// �X�v���C�g�t�H���g���擾�B
/// </summary>
/// <returns>�X�v���C�g�t�H���g</returns>
static inline DirectX::SpriteFont* GetSpriteFontGraphicsEngine()
{
	return GraphicsEngine::GetInstance()->GetSpriteFont();
}