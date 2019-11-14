#pragma once
#include "physics/ICollider.h"
class BoxCollider : public ICollider
{
public:
	BoxCollider();
	~BoxCollider();

	/// <summary>
	/// ボックスコライダーを作成
	/// </summary>
	/// <param name="size">大きさ</param>
	void Create(const CVector3& size);
	btCollisionShape* GetBody() const override
	{
		return shape;
	}

private:
	btBoxShape* shape;
};

