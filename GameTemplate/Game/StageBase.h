#pragma once
#include "IGameObject.h"
#include "physics/PhysicsStaticObject.h"

/// <summary>
/// ステージごとに特殊処理が入る可能性を考慮して、基底クラスを用意。 
/// </summary>
class StageBase : public IGameObject
{
public:
	StageBase();
	~StageBase();

	bool Start() override;

	 void Update() override;
	 /// <summary>
	 /// ステージ固有の更新処理を記述。
	 /// </summary>
	 virtual void LocalUpdate() 
	 {

	 }
	 /// <summary>
	 /// .cmoファイルのファイルパスを取得。
	 /// </summary>
	 /// <returns></returns>
	 virtual const wchar_t* GetCMOFilePath() const = 0;

	 /// <summary>
	 /// ステージの座標を設定。
	 /// </summary>
	 /// <param name="pos">座標</param>
	 void SetPosition(const CVector3& pos)
	 {
		 m_position = pos;
	 }

	 /// <summary>
	 /// ステージの回転を設定。
	 /// </summary>
	 /// <param name="rot">回転</param>
	 void SetRotation(const CQuaternion rot)
	 {
		 m_rotation = rot;
	 }

private:
	SkinModelRender* m_skinModel = nullptr;				//スキンモデル

	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率

	PhysicsStaticObject m_staticObject;		//静的オブジェクト
};

