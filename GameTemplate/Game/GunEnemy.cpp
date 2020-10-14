#include "stdafx.h"
#include "GunEnemy.h"
#include "Player.h"
#include "GunEnemyBullet.h"

const int GUNENEMY_BULLET_TIME = 30;			//�K���G�l�~�[���e�ۂ𔭎˂���^�C���B
const float GUNENEMY_BULLET_POSITION_Y = 120.0f;	//�K���G�l�~�[�̒e�ۂ𔭎˂���Y���W�B
const float GUNENEMY_DEATH_SE_VOLUME = 1.5f;				//�K���G�l�~�|���|���ꂽ����SE�̃{�����[��

GunEnemy::GunEnemy()
{
	//���f���̏������B
	m_skinModel = NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/GunEnemy.cmo");

	//�A�j���[�V���������[�h�B
	m_animClip[enAnim_wait].Load(L"Assets/animData/GunEnemy-wait.tka");
	m_animClip[enAnim_attack].Load(L"Assets/animData/GunEnemy-attack.tka");
	m_animClip[enAnim_found].Load(L"Assets/animData/GunEnemy-found.tka");

	//�A�j���[�V�����̃��[�v�t���O��ݒ�B
	m_animClip[enAnim_wait].SetLoopFlag(true);
	m_animClip[enAnim_attack].SetLoopFlag(true);

	//�A�j���[�V�����̏�����
	m_animation.Init(m_skinModel->GetSkinModel(), m_animClip, enAnim_num);

	//�K���G�l�~�[�̏����A�j���[�V����
	m_enAnimClip = enAnim_wait;

	//�G�t�F�N�g�̐����B
	m_gunEnemyDeathEffekt = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/EnemyDeath.efk");
	m_gunEnemySandDustEffekt = Effekseer::Effect::Create(g_effekseerManager, (const EFK_CHAR*)L"Assets/effect/GunEnemySandDust.efk");	

	//��Ԃ�����������B
	m_gunEnemyStateWait.Init(this);
	m_gunEnemyStateAttack.Init(this);
	m_gunEnemyStateFound.Init(this);

	//�K���G�l�~�[�̏������
	m_currentState = &m_gunEnemyStateWait;
}

GunEnemy::~GunEnemy()
{
	DeleteGO(m_gunBullet);
	//�X�L�����f�����폜�B
	DeleteGO(m_skinModel);
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
	//�A�j���[�V�����̍X�V�B
	m_animation.Update(GameTime().GetFrameDeltaTime());

	//�V���h�E�L���X�^�[��ݒ�B
	m_skinModel->SetShadowCaster();

	//�g�D�[�������_�[��ݒ�B
	m_skinModel->SetToonRender();

	//�X�L�����f���̍��W��ݒ�B
	m_skinModel->SetPosition(m_position);

	//�X�L�����f���̉�]��ݒ�B
	m_skinModel->SetRotation(m_rotation);
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
		//�T�E���h�̍Đ��B
		prefab::CSoundSource* gunEnemySE_Shot = NewGO<prefab::CSoundSource>();
		gunEnemySE_Shot->Init(L"Assets/Sound/GunEnemy_shot.wav");
		gunEnemySE_Shot->Play(false);

		//�e�ۂ̐����B
		m_gunBullet = NewGO<GunEnemyBullet>();
		m_gunBullet->SetPlayer(m_player);
		m_gunBullet->SetMoveSpd(gunEnemyFoward);
		m_gunBullet->SetPosition(positionY);
		m_bulletTimer = 0;
	}
}

void GunEnemy::Death()
{
	//�G�t�F�N�g��\���B
	m_playEffectHandle = g_effekseerManager->Play(m_gunEnemyDeathEffekt, m_position.x, m_position.y, m_position.z);

	//�T�E���h�̍Đ��B
	prefab::CSoundSource* gunEnemySE_death = NewGO<prefab::CSoundSource>();
	gunEnemySE_death->Init(L"Assets/Sound/EnemySE_Death.wav");
	gunEnemySE_death->Play(false);
	gunEnemySE_death->SetVolume(GUNENEMY_DEATH_SE_VOLUME);

	DeleteGO(this);
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
