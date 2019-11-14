#pragma once
#include "IGameObject.h"
class IGameObjectManager
{
public:
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	/// <summary>
	/// �Q�[���I�u�W�F�N�g��ǉ��B
	/// </summary>
	template <class T>
	T* NewGO()
	{
		T* newObj = new T;
		m_goList.push_back(newObj);
		return newObj;
	}

	void DeleteGO(IGameObject* go)
	{
		//���X�g���猟�����āA����������폜����B
		for (auto it = m_goList.begin();
			it != m_goList.end();
			it++
			) {
			if ((*it) == go) {
				go->RequestDelete();
			}
		}
	}
private:
	//IGameObject*�̉ϒ��z���
	//�����o�ϐ��ɒǉ�����B
	std::vector<IGameObject*> m_goList;		//�Q�[���I�u�W�F�N�g�̃��X�g
};

//�O������A�N�Z�X����̂ŁAextern�錾���K�v�B
extern IGameObjectManager g_goMgr;