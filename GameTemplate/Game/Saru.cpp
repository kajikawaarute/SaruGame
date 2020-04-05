#include "stdafx.h"
#include "Saru.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "BananaPeel.h"

Saru::Saru()
{
	m_model.Init(L"Assets/modelData/Saru.cmo");

	//�A�j���[�V���������[�h
	m_animClip[enAnim_taiki].Load(L"Assets/animData/Saru-taiki.tka");
	m_animClip[enAnim_run].Load(L"Assets/animData/Saru-run.tka");
	m_animClip[enAnim_attack].Load(L"Assets/animData/Saru-Attack.tka");
	m_animClip[enAnim_Get].Load(L"Assets/animData/Saru-Get.tka");

	//�A�j���[�V�����̃��[�v��ݒ�
	m_animClip[enAnim_taiki].SetLoopFlag(true);
	m_animClip[enAnim_run].SetLoopFlag(true);

	//�T���̏����A�j���[�V����
	m_enAnimClip = enAnim_taiki;

	//�T���̏������
	m_enSaruState = enState_taiki;

	//�A�j���[�V�����̏�����
	m_animation.Init(m_model, m_animClip, enAnim_num);

	//�T�E���h�\�[�X�̏�����
	m_saru_getAmiSE.Init(L"Assets/Sound/SaruSE_Get.wav");
	m_saru_attackSE.Init(L"Assets/Sound/SaruSE_Attack.wav");

	//Effekseer���������B
	InitEffekseer();
	//�G�t�F�N�g�����[�h
	m_effekt = Effekseer::Effect::Create(m_effekseerManager, (const EFK_CHAR*)L"Assets/effect/SaruGet.efk");
}

Saru::~Saru()
{
}

void Saru::Update()
{

	CVector3 saruFoward = CVector3::AxisZ();
	m_rotation.Multiply(saruFoward);
	//�T������v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toSaruDir = m_pl->GetPos() - m_position;
	float toSaruLen = toSaruDir.Length();
	toSaruDir.Normalize();

	float d = saruFoward.Dot(toSaruDir);

	float angle = acos(d);

	//�T���̏��
	switch (m_enSaruState)
	{
	case Saru::enState_taiki:	//�ҋ@���
		Move();
		m_enAnimClip = enAnim_taiki;
		m_moveSpeed = CVector3::Zero();
		if (fabsf(angle) < CMath::DegToRad(90.0f) && toSaruLen < 500.0f)
		{
			m_enSaruState = enState_run;
		}
		Distance();
		break;
	case Saru::enState_run:		//������
		Move();
		BanaPeelThrow();
		m_enAnimClip = enAnim_run;
		m_moveSpeed = toSaruDir;
		if (toSaruLen > 700.0f)
		{
			m_enSaruState = enState_taiki;
		}
		Distance();
		break;
	case Saru::enState_attack:	//�U�����
		Attack();
		m_taikiTimer++;
		if (m_taikiTimer == 60) {
			m_enSaruState = enState_taiki;
			m_enAnimClip = enAnim_taiki;
			m_taikiTimer = 0;
		}
		break;
	case Saru::enState_Get:		//�ߊl���
		m_enAnimClip = enAnim_Get;
		break;
	}

	//�T���̃A�j���[�V����
	switch (m_enAnimClip)
	{
	case Saru::enAnim_taiki:		//�ҋ@�A�j���[�V����
		m_animation.Play(enAnim_taiki, m_animTime);
		break;
	case Saru::enAnim_run:			//����A�j���[�V����
		m_animation.Play(enAnim_run, m_animTime);
		break;
	case Saru::enAnim_attack:		//�U���A�j���[�V����
		m_saru_attackSE.Play(false);
		m_animation.Play(enAnim_attack, m_animTime);
		break;
	case Saru::enAnim_Get:			//�ߊl�A�j���[�V����
		m_saru_getAmiSE.Play(false);
		m_animation.Play(enAnim_Get, m_animTime);
		break;
	}

	m_animation.Update(1.0f / 30.0f);
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	EffekseerCamera();
	//Effekseer���X�V
	m_effekseerManager->Update();
}

void Saru::Move()
{
	m_moveSpeed.Normalize();
	m_moveSpeed.x *= 5.0f;
	m_moveSpeed.z *= 5.0f;
	m_moveSpeed.y = 0.0f;
	m_position -= m_moveSpeed;

	Turn();
}

void Saru::Draw()
{
	m_effekseerRenderer->BeginRendering();
	m_effekseerManager->Draw();
	m_effekseerRenderer->EndRendering();

	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Saru::GetSaru()
{
	m_enSaruState = enState_Get;
	m_deathTimer++;
	if (m_deathTimer == 1) {
		//�G�t�F�N�g���Đ��B
		m_playEffectHandle = m_effekseerManager->Play(m_effekt, m_position.x, m_position.y, m_position.z);
	}
	if (m_deathTimer == 30) {
		g_goMgr.DeleteGO(this);
		m_pl->DeleteSaru(this);
	}
}

void Saru::Turn()
{
	CVector3 toSaruDir = m_pl->GetPos() - m_position;

	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}

	m_rotation.SetRotation(CVector3::AxisY(), atan2f(-toSaruDir.x, -toSaruDir.z));
}

void Saru::BanaPeelThrow()
{
	CVector3 saruFoward = CVector3::Back();
	m_rotation.Multiply(saruFoward);

	CVector3 moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;

	//�o�i�i�̔�𓊂���
	m_banaPeelTimer++;
	if (moveSpeedXZ.LengthSq() >= 1.0f * 1.0f && m_banaPeelTimer > 90) {
		m_banaPeel = g_goMgr.NewGO<BananaPeel>();
		m_banaPeel->SetPlayer(m_pl);
		m_banaPeel->SetMoveSpd(saruFoward);
		m_banaPeel->SetPosition(m_position);
		m_banaPeelTimer = 0;
	}
}

void Saru::InitEffekseer()
{
	//�����_���[���������B
	m_effekseerRenderer = EffekseerRendererDX11::Renderer::Create(
		g_graphicsEngine->GetD3DDevice(),			//D3D�f�o�C�X�B
		g_graphicsEngine->GetD3DDeviceContext(),	//D3D�f�o�C�X�R���e�L�X�g�B
		20000										//�|���̍ő吔�B
	);
	//�G�t�F�N�g�}�l�[�W�����������B
	m_effekseerManager = Effekseer::Manager::Create(10000);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	m_effekseerManager->SetSpriteRenderer(m_effekseerRenderer->CreateSpriteRenderer());
	m_effekseerManager->SetRibbonRenderer(m_effekseerRenderer->CreateRibbonRenderer());
	m_effekseerManager->SetRingRenderer(m_effekseerRenderer->CreateRingRenderer());
	m_effekseerManager->SetTrackRenderer(m_effekseerRenderer->CreateTrackRenderer());
	m_effekseerManager->SetModelRenderer(m_effekseerRenderer->CreateModelRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	m_effekseerManager->SetTextureLoader(m_effekseerRenderer->CreateTextureLoader());
	m_effekseerManager->SetModelLoader(m_effekseerRenderer->CreateModelLoader());
}

void Saru::EffekseerCamera()
{
	//Effekseer�J�����s���ݒ�B
	//�܂���Effeseer�̍s��^�̕ϐ��ɁA�J�����s��ƃv���W�F�N�V�����s����R�s�[�B
	Effekseer::Matrix44 efCameraMat;
	g_camera3D.GetViewMatrix().CopyTo(efCameraMat);
	Effekseer::Matrix44 efProjMat;
	g_camera3D.GetProjectionMatrix().CopyTo(efProjMat);
	//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
	m_effekseerRenderer->SetCameraMatrix(efCameraMat);
	m_effekseerRenderer->SetProjectionMatrix(efProjMat);
}

void Saru::Distance()
{
	//�T������v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toSaruDir = m_pl->GetPos() - m_position;
	float toSaruLen = toSaruDir.Length();

	if (toSaruLen < 90.0f) {
		m_enSaruState = enState_attack;
	}
}

void Saru::Attack()
{
	m_enAnimClip = enAnim_attack;
	//�T������v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toSaruDir = m_pl->GetPos() - m_position;

	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toSaruDir.x, toSaruDir.z));

	m_pl->GetMoveSpd() = toSaruDir * 2.0f;

	m_pl->Attacked();
}
