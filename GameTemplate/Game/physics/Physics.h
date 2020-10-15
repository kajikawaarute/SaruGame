#pragma once


class RigidBody;
class CharacterController;

class PhysicsWorld
{
	btDefaultCollisionConfiguration*		collisionConfig = nullptr;
	btCollisionDispatcher*					collisionDispatcher = nullptr;	//!<衝突解決処理。
	btBroadphaseInterface*					overlappingPairCache = nullptr;	//!<ブロードフェーズ。衝突判定の枝切り。
	btSequentialImpulseConstraintSolver*	constraintSolver = nullptr;		//!<コンストレイントソルバー。拘束条件の解決処理。
	btDiscreteDynamicsWorld*				dynamicWorld = nullptr;			//!<ワールド。
private:
	//コンストラクタとデストラクタをprivateに宣言して、
	//外部からインスタンスを作成できないようにする。
	PhysicsWorld() {}
	~PhysicsWorld();
public:
	/// <summary>
	/// フィジックスのインスタンスを取得。
	/// </summary>
	/// <returns>フィジックスのインスタンス</returns>
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
	* @brief	ダイナミックワールドを取得。
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
	}
	/*!
	* @brief	剛体を登録。
	*/
	void AddRigidBody(RigidBody& rb);
	/*!
	* @brief	剛体を破棄。
	*/
	void RemoveRigidBody(RigidBody& rb);

	/// <summary>
	/// コリジョンオブジェクトを登録。
	/// </summary>
	/// <param name="collObj">コリジョンオブジェクト</param>
	void AddCollisionObject(btCollisionObject& collObj);

	/// <summary>
	/// コリジョンオブジェクトを破棄。
	/// </summary>
	/// <param name="collObj">コリジョンオブジェクト</param>
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
	/// キャラクターコントローラーとの当たり判定処理。
	/// </summary>
	/// <param name="charaCon">キャラクターコントローラー</param>
	/// <param name="cb">衝突を判定するオブジェクト</param>
	void ContactTest(CharacterController& charaCon, std::function<void(const btCollisionObject& contactCollisionObject)>cb);
};

//ヘルパー関数

/// <summary>
/// キャラクターコントローラーとの当たり判定処理。
/// </summary>
/// <param name="charaCon">キャラクターコントローラー</param>
/// <param name="cb">衝突を判定するオブジェクト</param>
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
/// 剛体を登録。
/// </summary>
/// <param name="rb">剛体</param>
static inline void AddRigidBodyPhysicsWorld(RigidBody& rb)
{
	PhysicsWorld::GetInstance()->AddRigidBody(rb);
}

/// <summary>
/// 剛体を破棄。
/// </summary>
/// <param name="rb">剛体</param>
static inline void RemoveRigidBodyPhysicsWorld(RigidBody& rb)
{
	PhysicsWorld::GetInstance()->RemoveRigidBody(rb);
}