#pragma once
#include "BoxCollider.h"

class PhysicsGhostObject
{
public:
	PhysicsGhostObject();
	~PhysicsGhostObject();

	void CreateBox(CVector3 pos, CQuaternion rot, CVector3 size);

	void Release();

	/// <summary>
	/// ゴースト作成処理の共通処理
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	void CreateCommon(CVector3 pos, CQuaternion rot);

	/// <summary>
	/// 引数で渡されたゴーストオブジェクトが自分自身か判定
	/// </summary>
	/// <param name="ghost">ゴーストオブジェクト</param>
	/// <returns></returns>
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}
private:

	bool m_isRegistPhysicsWorld = false;	//物理ワールドに登録しているかのどうかのフラグ
	btGhostObject m_ghostObject;			//ゴースト

	std::unique_ptr<ICollider> m_collider;	//コライダー
};

