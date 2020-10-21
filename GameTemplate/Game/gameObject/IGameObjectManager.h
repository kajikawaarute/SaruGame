#pragma once
#include "IGameObject.h"
class IGameObjectManager
{
	private:
	//�R���X�g���N�^�ƃf�X�g���N�^��private�ɐ錾���āA
	//�O������C���X�^���X���쐬�ł��Ȃ��悤�ɂ���B
	IGameObjectManager() {}
	~IGameObjectManager() {}
public:
	/// <summary>
	/// IGameObjectManager�̃C���X�^���X���擾����B
	/// </summary>
	/// <returns>IGameObjectManager�̃C���X�^���X</returns>
	static IGameObjectManager* GetInstance()
	{
		static IGameObjectManager* instance = nullptr;
		if (instance == nullptr) {
			instance = new IGameObjectManager();
		}
		return instance;
	}
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

	/// <summary>
	/// �Q�[���I�u�W�F�N�g���폜�B
	/// </summary>
	/// <param name="go">�폜����Q�[���I�u�W�F�N�g</param>
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
	std::list<IGameObject*> m_goList;		//�Q�[���I�u�W�F�N�g�̃��X�g
};

//�w���p�[�֐�
/// <summary>
/// �Q�[���I�u�W�F�N�g��ǉ��B
/// </summary>
template <class T>
static inline T* NewGO()
{
	return IGameObjectManager::GetInstance()->NewGO<T>();
}

/// <summary>
/// �Q�[���I�u�W�F�N�g���폜�B
/// </summary>
/// <param name="go">�폜����Q�[���I�u�W�F�N�g</param>
static inline void DeleteGO(IGameObject* go)
{
	IGameObjectManager::GetInstance()->DeleteGO(go);
}