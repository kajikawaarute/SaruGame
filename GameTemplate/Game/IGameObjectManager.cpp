#include "stdafx.h"
#include "IGameObjectManager.h"

//IGameObjectManager�N���X�̃C���X�^���X�B
IGameObjectManager g_goMgr;

void IGameObjectManager::Update()
{
	for (auto go : m_goList) {
		go->Start();
	}
	int i = 0;
	//�o�^����Ă���Q�[���I�u�W�F�N�g�̍X�V�������ĂԁB
	for (auto go : m_goList) {
		go->Update();
		i++;
	}
	for (auto go : m_goList) {
		go->Draw();
	}

	//���ׂẴQ�[���I�u�W�F�N�g��
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

