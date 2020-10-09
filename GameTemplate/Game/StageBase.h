#pragma once
#include "physics/PhysicsStaticObject.h"

/// <summary>
/// ステージごとに特殊処理が入る可能性を考慮して、基底クラスを用意。 
/// </summary>
class StageBase : public IGameObject
{
public:
	StageBase();
	~StageBase();

	/// <summary>
	/// StageBaseのUpdate関数前に呼ばれる開始関数。
	/// </summary>
	/// <returns>trueを返すと一度だけ呼ばれる</returns>
	bool Start() override;

	/// <summary>
	/// StageBaseの更新関数。
	/// </summary>
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
	/// <returns>ステージのファイルパス</returns>
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

	/// <summary>
	/// サルの数を設定。
	/// </summary>
	/// <param name="saruNo">サルの数</param>
	 void SetSaruNo(const int &saruNo)
	 {
		 m_saruNo = saruNo;
	 }

	 /// <summary>
	 /// 倒すエネミーの数を設定。
	 /// </summary>
	 /// <param name="eneNo">エネミーの数</param>
	 void SetDownEnemyNo(const int &eneNo)
	 {
		 m_downEnemyNo = eneNo;
	 }

	 /// <summary>
	 /// 捕まえたサルの数を設定。
	 /// </summary>
	 /// <param name="saruCount">捕まえたサルの数</param>
	 void SetSaruCounter(const int &saruCount)
	 {
		 m_getSaruCount = saruCount;
	 }

	 /// <summary>
	 /// 倒したエネミーの数を設定。
	 /// </summary>
	 /// <param name="eneCount">倒したエネミーの数</param>
	 void SetDownEnemyCounter(const int &eneCount)
	 {
		 m_downEnemyCount = eneCount;
	 }

	 /// <summary>
	 /// ゲームオーバーのフラグを設定。
	 /// </summary>
	 /// <param name="flag">フラグ</param>
	 /// <returns>ゲームオーバーのフラグ</returns>
	 bool SetGameOverFlag(bool flag)
	 {
		 m_gameOverFlag = flag;
		 return m_gameOverFlag;
	 }

	 /// <summary>
	 /// ゲームクリアタイマーを取得。
	 /// </summary>
	 /// <returns>ゲームクリアタイマー</returns>
	 int GetClearTimer()
	 {
		 return m_gameClearTimer;
	 }

	 /// <summary>
	 /// ゲームオーバータイマーを取得。
	 /// </summary>
	 /// <returns>ゲームオーバータイマー</returns>
	 int GetOverTimer()
	 {
		 return m_gameOverTimer;
	 }
protected:
	int m_saruNo = 0;				//サルの数。
	int m_getSaruCount = 0;			//捕まえたサルの数。
	int m_downEnemyNo = 0;			//倒すエネミーの数。
	int m_downEnemyCount = 0;		//倒したエネミーの数。
	int m_gameClearTimer = 0;		//ゲームクリアまでのタイマー
	int m_gameOverTimer = 0;		//ゲームオーバーのまでのタイマー
	bool m_gameOverFlag = false;	//ゲームオーバーのフラグ
private:
	SkinModelRender* m_skinModel = nullptr;				//スキンモデル

	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率

	PhysicsStaticObject m_staticObject;		//静的オブジェクト
};

