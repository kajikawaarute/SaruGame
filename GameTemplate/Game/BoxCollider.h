#pragma once
#include "physics/ICollider.h"
class BoxCollider : public ICollider
{
public:
	BoxCollider();
	~BoxCollider();

	/// <summary>
	/// �{�b�N�X�R���C�_�[���쐬
	/// </summary>
	/// <param name="size">�傫��</param>
	void Create(const CVector3& size);
	btCollisionShape* GetBody() const override
	{
		return shape;
	}

private:
	btBoxShape* shape;
};

