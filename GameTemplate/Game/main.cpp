#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "Title.h"
#include "sound/SoundEngine.h"

Effekseer::Manager* g_effekseerManager = nullptr;
EffekseerRenderer::Renderer* g_effekseerRenderer = nullptr;

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//Title�N���X�̃C���X�^���X
	Title* title = NewGO<Title>();

	//�T�E���h�G���W���̃C���X�^���X
	CSoundEngine soundEngine;
	//�T�E���h�G���W���̏�����
	soundEngine.Init();

	//Effekseer�}�l�[�W���[�Ǘ�
	//�����_���[���������B
	g_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		GetD3DDeviceGraphicsEngine(),			//D3D�f�o�C�X�B
		GetD3DDeviceContextGraphicsEngine(),	//D3D�f�o�C�X�R���e�L�X�g�B
		20000									//�|���̍ő吔�B
	);
	//�G�t�F�N�g�}�l�[�W�����������B
	g_effekseerManager = Effekseer::Manager::Create(10000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	g_effekseerManager->SetSpriteRenderer(g_effekseerRenderer->CreateSpriteRenderer());
	g_effekseerManager->SetRibbonRenderer(g_effekseerRenderer->CreateRibbonRenderer());
	g_effekseerManager->SetRingRenderer(g_effekseerRenderer->CreateRingRenderer());
	g_effekseerManager->SetTrackRenderer(g_effekseerRenderer->CreateTrackRenderer());
	g_effekseerManager->SetModelRenderer(g_effekseerRenderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	g_effekseerManager->SetTextureLoader(g_effekseerRenderer->CreateTextureLoader());
	g_effekseerManager->SetModelLoader(g_effekseerRenderer->CreateModelLoader());

	CStopwatch sw;
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//1�t���[���̎��Ԍv�����J�n�B
		sw.Start();
		//�`��J�n�B
		GraphicsEngine::GetInstance()->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V
		IGameObjectManager::GetInstance()->Update();

		g_effekseerRenderer->BeginRendering();
		g_effekseerManager->Draw();
		g_effekseerRenderer->EndRendering();

		//Effekseer���X�V
		g_effekseerManager->Update();

		//Effekseer�J�����s���ݒ�B
		//�܂���Effeseer�̍s��^�̕ϐ��ɁA�J�����s��ƃv���W�F�N�V�����s����R�s�[�B
		Effekseer::Matrix44 efCameraMat;
		g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
		Effekseer::Matrix44 efProjMat;
		g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
		//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
		g_effekseerRenderer->SetCameraMatrix(efCameraMat);
		g_effekseerRenderer->SetProjectionMatrix(efProjMat);

		//�J�����̍X�V�B
		g_camera3D.Update();
		//�T�E���h�G���W���̍X�V
		soundEngine.Update();
		//�`��I���B
		GraphicsEngine::GetInstance()->EndRender();
		//1�t���[���̎��Ԍv�����I���B
		sw.Stop();
		//�o�ߎ��Ԃ��L�����Ă����B
		GameTime().PushFrameDeltaTime(sw.GetElapsed());
	}
}