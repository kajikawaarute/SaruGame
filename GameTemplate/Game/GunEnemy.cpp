#include "stdafx.h"
#include "GunEnemy.h"
#include "IGameObjectManager.h"
#include "Player.h"
#include "GunEnemyBullet.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"


const float GUNENEMY_ATTACK_DISTANCE = 600.0f;		//�K���G�l�~�[���U��������͈́B
const int GUNENEMY_BULLET_TIME = 30;			//�K���G�l�~�[���e�ۂ𔭎˂���^�C���B
const float GUNENEMY_BULLET_POSITION_Y = 120.0f;	//�K���G�l�~�[�̒e�ۂ𔭎˂���Y���W�B

GunEnemy::GunEnemy()
{
	m_model.Init(L"Assets/modelData/GunEnemy.cmo");

	//�A�j���[�V���������[�h�B
	m_animClip[enAnim_wait].Load(L"Assets/animData/GunEnemy-wait.tka");
	m_animClip[enAnim_attack].Load(L"Assets/animData/GunEnemy-attack.tka");
	m_animClip[enAnim_found].Load(L"Assets/animData/GunEnemy-found.tka");

	//�G�t�F�N�g�̐����B
	m_gunEnemyDeathEffekt = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/EnemyDeath.efk");

	//�A�j���[�V�����̃��[�v�t���O��ݒ�B
	m_animClip[enAnim_wait].SetLoopFlag(true);
	m_animClip[enAnim_attack].SetLoopFlag(true);

	//��Ԃ�����������B
	m_gunEnemyStateWait.Init(this);
	m_gunEnemyStateAttack.Init(this);
	m_gunEnemyStateFound.Init(this);

	//�A�j���[�V�����̏�����
	m_animation.Init(m_model, m_animClip, enAnim_num);

	//�K���G�l�~�[�̏����A�j���[�V����
	m_enAnimClip = enAnim_wait;

	//�K���G�l�~�[�̏������
	m_currentState = &m_gunEnemyStateWait;

	//�V���h�E���V�[�o�[��ݒ�B
	m_model.SetShadowReciever(true);
}

GunEnemy::~GunEnemy()
{
}

void GunEnemy::Update()
{
	//�K���G�l�~�[�̏��
	m_currentState->Update();
	ChangeState(m_enGunEnemyState);

	switch (m_enAnimClip)
	{
	case GunEnemy::enAnim_wait:		//�ҋ@�A�j���[�V����
		m_animation.Play(enAnim_wait, m_animTime);
		break;
	case GunEnemy::enAnim_attack:	//�U���A�j���[�V����
		m_animation.Play(enAnim_attack, m_animTime);
		break;
	case GunEnemy::enAnim_found:	//�����������̃A�j���[�V����
		m_animation.Play(enAnim_found, m_animTime);
		break;
	}
	m_animation.Update(GameTime().GetFrameDeltaTime());

	//�V���h�E�L���X�^�[��ݒ�B
	ShadowMap::GetInstance().RegistShadowCaster(&m_model);

	//�g�D�[�������_�[��ݒ�B
	ToonRender::GetInstance().RegistToonRender(&m_model);

	//���[���h�s��̍X�V
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void GunEnemy::Draw()
{
	m_model.Draw(
		enRenderMode_Normal, 
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

void GunEnemy::Attack()
{
	CVector3 positionY = m_position;
	positionY.y = m_position.y + GUNENEMY_BULLET_POSITION_Y;

	//�K���G�l�~�[�̑O�������v�Z����B
	CVector3 gunEnemyFoward = CVector3::AxisZ();
	m_rotation.Multiply(gunEnemyFoward);

	m_bulletTimer++;
	if (m_bulletTimer == GUNENEMY_BULLET_TIME) {
		GunEnemyBullet* gunBullet = g_goMgr.NewGO<GunEnemyBullet>();
		gunBullet->SetPlayer(m_player);
		gunBullet->SetMoveSpd(gunEnemyFoward);
		gunBullet->SetPosition(positionY);
		m_bulletTimer = 0;
	}
}

void GunEnemy::AttackDistance()
{
	//�K���G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toSaruDir = m_player->GetPos() - m_position;
	float toSaruLen = toSaruDir.Length();

	//�v���C���[��������͈́B
	if (toSaruLen < GUNENEMY_ATTACK_DISTANCE) {
		m_enGunEnemyState = enState_found;
	}
}

void GunEnemy::Death()
{
	//�G�t�F�N�g��\���B
	m_playEffectHandle = g_effekseerManager->Play(m_gunEnemyDeathEffekt, m_position.x, m_position.y, m_position.z);

	g_goMgr.DeleteGO(this);
	m_player->DeleteGunEnemy(this);
}

void GunEnemy::ChangeState(EnGunEnemyState nextState)
{
	IGunEnemyState* pNextState = nullptr;
	EnAnimationClip nextAnimClip = enAnim_wait;
	switch (nextState)
	{
	case GunEnemy::enState_wait:
		//���݂̏�Ԃ�ҋ@��Ԃɂ���B
		pNextState = &m_gunEnemyStateWait;
		nextAnimClip = enAnim_wait;
		break;
	case GunEnemy::enState_attack:
		//���݂̏�Ԃ��U����Ԃɂ���B
		pNextState = &m_gunEnemyStateAttack;
		nextAnimClip = enAnim_attack;
		break;
	case GunEnemy::enState_found:
		//���݂̏�Ԃ�����������Ԃɂ���B
		pNextState = &m_gunEnemyStateFound;
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
