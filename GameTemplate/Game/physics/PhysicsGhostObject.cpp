#include "stdafx.h"
#include "PhysicsGhostObject.h"
#include "BoxCollider.h"


PhysicsGhostObject::PhysicsGhostObject()
{
}


PhysicsGhostObject::~PhysicsGhostObject()
{
	Release();
}

void PhysicsGhostObject::CreateBox(CVector3 pos, CQuaternion rot, CVector3 size)
{
	Release();
	auto boxCollider = std::make_unique<BoxCollider>();
	boxCollider->Create(size);
	m_collider = std::move(boxCollider);
	CreateCommon(pos, rot);
}

void PhysicsGhostObject::Release()
{
	if (m_isRegistPhysicsWorld == true) {
		PhysicsWorld::GetInstance()->RemoveCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = false;
	}
}

void PhysicsGhostObject::CreateCommon(CVector3 pos, CQuaternion rot)
{
	m_ghostObject.setCollisionShape(m_collider->GetBody());
	btTransform btTrans;
	btTrans.setOrigin({ pos.x, pos.y, pos.z });
	btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w});
	m_ghostObject.setWorldTransform(btTrans);

	//•¨—ƒGƒ“ƒWƒ“‚É“o˜^B
	PhysicsWorld::GetInstance()->AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;
}

void PhysicsGhostObject::SetPosition(const CVector3& pos)
{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btVector3 btPos;
		pos.CopyTo(btPos);
		btTrans.setOrigin(btPos);
}
