#include "stdafx.h"
#include "Saru.h"
#include "Player.h"
#include "IGameObjectManager.h"
#include "BananaPeel.h"
#include "BikkuriMark.h"

const float SARU_MOVE_SPPED = 300.0f;			//�T���̈ړ����x�B
const float SARU_FUTTOBI_POWER = 2500.0f;		//�T���̃v���C���[�𐁂���΂��́B

Saru::Saru()
{
	m_model.Init(L"Assets/modelData/Saru.cmo");

	//�A�j���[�V���������[�h
	m_animClip[enAnim_wait].Load(L"Assets/animData/Saru-taiki.tka");
	m_animClip[enAnim_run].Load(L"Assets/animData/Saru-run.tka");
	m_animClip[enAnim_attack].Load(L"Assets/animData/Saru-Attack.tka");
	m_animClip[enAnim_Get].Load(L"Assets/animData/Saru-Get.tka");
	m_animClip[enAnim_found].Load(L"Assets/animData/Saru-found.tka");

	//�G�t�F�N�g�����[�h
	m_saruGetEffekt = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/SaruGet.efk");
	m_saruRunEffect = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/SaruRun.efk");
	m_saruDamegeEffect = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/SaruDamege.efk");

	//�A�j���[�V�����̃��[�v��ݒ�
	m_animClip[enAnim_wait].SetLoopFlag(true);
	m_animClip[enAnim_run].SetLoopFlag(true);

	//�T���̏����A�j���[�V����
	m_enAnimClip = enAnim_wait;

	//�T���̏������
	m_currentState = &m_saruStateWait;
	m_enSaruState = enState_wait;

	//�A�j���[�V�����̏�����
	m_animation.Init(m_model, m_animClip, enAnim_num);

	//��Ԃ�����������B
	m_saruStateWait.Init(this);
	m_saruStateRun.Init(this);
	m_saruStateAttack.Init(this);
	m_saruStateGet.Init(this);
	m_saruStateStun.Init(this);
	m_saruStateFound.Init(this);
}

Saru::~Saru()
{
}

void Saru::Update()
{
	//�G�l�~�|�̏��
	m_currentState->Update();
	ChangeState(m_enSaruState);

	//�p�X�ړ�
	if (m_pathList.size() > 0)
	{
		if (m_enSaruState == enState_wait) {
			auto diff = m_position - m_pathList[pathNum];
			if (diff.Length() < 50.0f)
			{
				if (pathNum < m_pathList.size() - 1)
				{
					pathNum++;
				}
				else pathNum = 0;
			}
			auto addSpeed = diff;
			addSpeed.Normalize();
			angle = atan2f(-addSpeed.x, -addSpeed.z);
			m_rotation.SetRotation(CVector3::AxisY(), angle);
			m_moveSpeed += addSpeed;
		}
	}
	//�T���̃A�j���[�V����
	switch (m_enAnimClip)
	{
	case Saru::enAnim_wait:			//�ҋ@�A�j���[�V����
		m_animation.Play(enAnim_wait, m_animTime);
		break;
	case Saru::enAnim_run:			//����A�j���[�V����
		m_animation.Play(enAnim_run, m_animTime);
		break;
	case Saru::enAnim_attack:		//�U���A�j���[�V����
		m_animation.Play(enAnim_attack, m_animTime);
		break;
	case Saru::enAnim_Get:			//�ߊl�A�j���[�V����
		m_animation.Play(enAnim_Get, m_animTime);
		break;
	case enState_stun:
		m_animation.Play(enAnim_Get, m_animTime);
		break;
	case enState_found:				//���������A�j���[�V����
		m_animation.Play(enAnim_found, m_animTime);
		break;
	}

	m_animation.Update(GameTime().GetFrameDeltaTime());
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Saru::Move()
{
	m_moveSpeed.Normalize();
	m_moveSpeed.x *= SARU_MOVE_SPPED;
	m_moveSpeed.z *= SARU_MOVE_SPPED;
	m_moveSpeed.y = 0.0f;

	m_position -= m_moveSpeed * GameTime().GetFrameDeltaTime();

	Turn();
}

void Saru::Run()
{
	m_moveSpeed.Normalize();
	m_moveSpeed.x *= SARU_MOVE_SPPED * 5.0f;
	m_moveSpeed.z *= SARU_MOVE_SPPED * 5.0f;
	m_moveSpeed.y = 0.0f;

	m_position -= m_moveSpeed * GameTime().GetFrameDeltaTime();

	Turn();
}

void Saru::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}

void Saru::GetSaru()
{
	m_enSaruState = enState_Get;
}

void Saru::Turn()
{
	CVector3 toSaruDir = m_pl->GetPos() - m_position;

	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	angle = atan2f(-toSaruDir.x, -toSaruDir.z);
	m_rotation.SetRotation(CVector3::AxisY(),angle );
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

void Saru::Stun()
{
	m_enSaruState = enState_stun;
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	if (m_animation.IsPlaying() != true) {
		m_enSaruState = enState_wait;
	}
}

void Saru::Found()
{
	CVector3 positionY = m_position;
	positionY.y = m_position.y + 160.0f;

	m_bikkuriMark = g_goMgr.NewGO<BikkuriMark>();
	m_bikkuriMark->SetPosition(positionY);

	//�T������v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toSaruDir = m_pl->GetPos() - m_position;
	//�v���C���[�̕�������
	angle = atan2f(toSaruDir.x, toSaruDir.z);
	m_rotation.SetRotation(CVector3::AxisY(),angle);

	g_goMgr.DeleteGO(m_bikkuriMark);

	if (m_animation.IsPlaying() != true) {
		m_enSaruState = enState_run;
	}
}

void Saru::AttackDistance()
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
	//�T������v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toSaruDir = m_pl->GetPos() - m_position;
	//�v���C���[�̕�������
	angle = atan2f(toSaruDir.x, toSaruDir.z);
	m_rotation.SetRotation(CVector3::AxisY(),angle );
	
	toSaruDir.Normalize();
	m_pl->SetAttackedPower(toSaruDir * SARU_FUTTOBI_POWER);
	m_pl->Attacked();

	//�T�E���h���Đ�
	prefab::CSoundSource* saruAttackSE = g_goMgr.NewGO<prefab::CSoundSource>();
	saruAttackSE->Init(L"Assets/Sound/SaruSE_Attack.wav");
	saruAttackSE->Play(false);
}

void Saru::Death()
{
	g_goMgr.DeleteGO(this);
	m_pl->DeleteSaru(this);
}

void Saru::ChangeStateWaitAnim()
{
	if (m_animation.IsPlaying() != true) {
		m_enSaruState = enState_wait;
	}
}

void Saru::SaruGetSound()
{
	prefab::CSoundSource* saruGetSE = g_goMgr.NewGO<prefab::CSoundSource>();
	saruGetSE->Init(L"Assets/Sound/SaruSE_Get.wav");
	saruGetSE->Play(false);
}

void Saru::ChangeState(EnSaruState nextState)
{
	ISaruState* pNextState = nullptr;
	EnAnimationClip nextAnimClip = enAnim_wait;
	switch (nextState)
	{
	case Saru::enState_wait:
		//���݂̏�Ԃ�ҋ@��Ԃɂ���B
		pNextState = &m_saruStateWait;
		nextAnimClip = enAnim_wait;
		break;
	case Saru::enState_run:
		//���݂̏�Ԃ𑖂��Ԃɂ���B
		pNextState = &m_saruStateRun;
		nextAnimClip = enAnim_run;
		break;
	case Saru::enState_attack:
		//���݂̏�Ԃ��U����Ԃɂ���B
		pNextState = &m_saruStateAttack;
		nextAnimClip = enAnim_attack;
		break;
	case Saru::enState_Get:
		//���݂̏�Ԃ�ߊl��Ԃɂ���B
		pNextState = &m_saruStateGet;
		nextAnimClip = enAnim_Get;
		break;
	case Saru::enState_stun:
		//���݂̏�Ԃ����ݏ�Ԃɂ���B
		pNextState = &m_saruStateStun;
		nextAnimClip = enAnim_Get;
		break;
	case Saru::enState_found:
		//���݂̏�Ԃ�����������Ԃɂ���B
		pNextState = &m_saruStateFound;
		nextAnimClip = enAnim_found;
		break;
	}
	if (pNextState != nullptr && pNextState != m_currentState) {
		//���݂̏�ԂƈႤ�B
		if (m_currentState != nullptr) {
			//�I������
			m_currentState->OnLeave();
		}
		m_currentState = pNextState;
		m_enAnimClip = nextAnimClip;
		//�J�n����
		m_currentState->OnEnter();
	}
}