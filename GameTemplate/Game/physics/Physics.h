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
private:
	//�R���X�g���N�^�ƃf�X�g���N�^��private�ɐ錾���āA
	//�O������C���X�^���X���쐬�ł��Ȃ��悤�ɂ���B
	PhysicsWorld() {}
	~PhysicsWorld();
public:
	/// <summary>
	/// �t�B�W�b�N�X�̃C���X�^���X���擾�B
	/// </summary>
	/// <returns>�t�B�W�b�N�X�̃C���X�^���X</returns>
	static PhysicsWorld* GetInstance()
	{
		static PhysicsWorld* instance = nullptr;
		if (instance == nullptr) {
			instance = new PhysicsWorld();
		}
		return instance;
	}

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

	/// <summary>
	/// �L�����N�^�[�R���g���[���[�Ƃ̓����蔻�菈���B
	/// </summary>
	/// <param name="charaCon">�L�����N�^�[�R���g���[���[</param>
	/// <param name="cb">�Փ˂𔻒肷��I�u�W�F�N�g</param>
	void ContactTest(CharacterController& charaCon, std::function<void(const btCollisionObject& contactCollisionObject)>cb);
};

//�w���p�[�֐�

/// <summary>
/// �L�����N�^�[�R���g���[���[�Ƃ̓����蔻�菈���B
/// </summary>
/// <param name="charaCon">�L�����N�^�[�R���g���[���[</param>
/// <param name="cb">�Փ˂𔻒肷��I�u�W�F�N�g</param>
static inline void ContactTestPhysicsWorld(CharacterController& charaCon, std::function<void(const btCollisionObject& contactCollisionObject)>cb)
{
	PhysicsWorld::GetInstance()->ContactTest(charaCon, cb);
}

static inline void ConvexSweepTestPhysicsWorld(
	const btConvexShape* castShape,
	const btTransform& convexFromWorld,
	const btTransform& convexToWorld,
	btCollisionWorld::ConvexResultCallback& resultCallback,
	btScalar allowedCcdPenetration = 0.0f
)
{
	PhysicsWorld::GetInstance()->ConvexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
}

/// <summary>
/// ���̂�o�^�B
/// </summary>
/// <param name="rb">����</param>
static inline void AddRigidBodyPhysicsWorld(RigidBody& rb)
{
	PhysicsWorld::GetInstance()->AddRigidBody(rb);
}

/// <summary>
/// ���̂�j���B
/// </summary>
/// <param name="rb">����</param>
static inline void RemoveRigidBodyPhysicsWorld(RigidBody& rb)
{
	PhysicsWorld::GetInstance()->RemoveRigidBody(rb);
}