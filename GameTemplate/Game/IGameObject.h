#pragma once
class IGameObject
{
public:
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// �`��֐�
	/// </summary>
	virtual void Draw() = 0;

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

private:
	bool isRequestDelete = false;	//�폜���N�G�X�g
};

