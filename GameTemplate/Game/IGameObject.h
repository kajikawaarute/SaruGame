#pragma once
class IGameObject
{
public:
	/// <summary>
	/// ���z�f�X�g���N�^�B
	/// </summary>
	virtual ~IGameObject() {}

	/// <summary>
	/// Update�̒��O�ŌĂ΂��J�n�����B
	/// </summary>
	/// <returns>true��Ԃ��ƃQ�[���I�u�W�F�N�g�̏��������������Ɣ��f�����
	/// Update�֐����Ă΂�o���Btrue��Ԃ��Ĉȍ~��Start�֐��͌Ă΂�Ȃ��Ȃ�B
	/// </returns>
	virtual bool Start()
	{
		return true;
	}

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`��֐�
	/// </summary>
	virtual void Draw() {}

	/// <summary>
	/// �폜���N�G�X�g���s��
	/// </summary>
	void RequestDelete()
	{
		isRequestDelete = true;
	}

	/// <summary>
	/// �폜���N�G�X�g���󂯂Ă��邩���ׂ�
	/// </summary>
	/// true���A���Ă�����󂯂Ă���
	bool IsRequestDelete()
	{
		return isRequestDelete;
	}

	void SetStart(bool start)
	{
		isStart = start;
	}

	bool GetisStart()
	{
		return isStart;
	}

private:
	bool isRequestDelete = false;	//�폜���N�G�X�g
	bool isStart = false;
};

