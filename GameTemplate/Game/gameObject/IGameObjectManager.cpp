#include "stdafx.h"
#include "IGameObjectManager.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"

//IGameObjectManager�N���X�̃C���X�^���X�B
IGameObjectManager g_goMgr;

void IGameObjectManager::Update()
{

	//�o�^����Ă���Q�[���I�u�W�F�N�g�̃X�^�[�g�֐����ĂԁB
	for (auto go : m_goList) {
		//�X�^�[�g�֐����Ă�ł��Ȃ�������ĂԁB
		if (!go->GetisStart()) {
			go->Start();
			go->SetStart(true);
		}
	}
	int i = 0;
	//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�������ĂԁB
	for (auto go : m_goList) {
		//�X�^�[�g�֐����Ă΂ꂽ�X�V�֐����ĂԁB
		if (go->GetisStart()) {
			go->Update();
		}
		i++;
	}

	//�V���h�E�}�b�v
	ShadowMap::GetInstance().Draw();

	//�g�D�[�������_�[
	ToonRender::GetInstance().Draw();

	//�o�^����Ă���Q�[���I�u�W�F�N�g�̕`�揈�����ĂԁB
	for (auto go : m_goList) {
		//�X�^�[�g�֐����Ă΂ꂽ�`��֐����ĂԁB
		if(go->GetisStart()) {
			go->Draw();
		}
	}

	//���ׂẴQ�[���I�u�W�F�N�g�̃��X�g�̌���
	for (auto it = m_goList.begin(); it != m_goList.end();) {
		if ((*it)->IsRequestDelete()) {
			//�폜���N�G�X�g���󂯂Ă���̂ō폜�B
			delete* it;
			it = m_goList.erase(it);
			//it++;
		}
		else {
			//���N�G�X�g���󂯂Ă��Ȃ��B
			it++;
		}
	}

}

