#pragma once


class RigidBody;
class CharacterController;

class PhysicsWorld
{
	btDefaultCollisionConfiguration*		collisionConfig = nullptr;
	btCollisionDispatcher*					collisionDispatcher = nullptr;	//!<�Փˉ��������B
	btBroadphaseInterface*					overlappingPairCache = nullptr;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
	btSequentialImpulseConstraintSolver*	constraintSolver = nullptr;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
	btDiscreteDynamicsWorld*				dynamicWorld = nullptr;			//!<���[���h�B
public:
	~PhysicsWorld();
	void Init();
	void Update();
	void Release();
	/*!
	* @brief	�_�C�i�~�b�N���[���h���擾�B
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
	}
	/*!
	* @brief	���̂�o�^�B
	*/
	void AddRigidBody(RigidBody& rb);
	/*!
	* @brief	���̂�j���B
	*/
	void RemoveRigidBody(RigidBody& rb);

	/// <summary>
	/// �R���W�����I�u�W�F�N�g��o�^�B
	/// </summary>
	/// <param name="collObj">�R���W�����I�u�W�F�N�g</param>
	void AddCollisionObject(btCollisionObject& collObj);

	/// <summary>
	/// �R���W�����I�u�W�F�N�g��j���B
	/// </summary>
	/// <param name="collObj">�R���W�����I�u�W�F�N�g</param>
	void RemoveCollisionObject(btCollisionObject& collObj);

	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f
	)
	{
		dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}
	void ContactText(
		btCollisionObject* colObj, 
		btCollisionWorld::ContactResultCallback& resultCallback
	)
	{
		dynamicWorld->contactTest(colObj, resultCallback);
	}

	void ContactTest(RigidBody& rb,std::function<void(const btCollisionObject& contactCollisionObject)>cb);

	void ContactTest(CharacterController& charaCon, std::function<void(const btCollisionObject& contactCollisionObject)>cb);
};

extern PhysicsWorld g_physics;


