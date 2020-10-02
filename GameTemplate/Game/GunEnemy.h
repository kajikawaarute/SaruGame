#pragma once
#include "IGameObject.h"

#include "GunEnemyStateWait.h"
#include "GunEnemyStateAttack.h"
#include "GunEnemyStateFound.h"

#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

class Player;
class GunEnemyBullet;
class GunEnemy : public IGameObject
{
public:
	GunEnemy();
	~GunEnemy();

	/// <summary>
	/// ガンエネミーの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// ガンエネミーの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// ガンエネミーの座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	/// <returns></returns>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ガンエネミーの回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// ガンエネミーの座標を取得。
	/// </summary>
	/// <returns>ガンエネミーの座標</returns>
	CVector3& GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// ガンエネミーの攻撃処理
	/// </summary>
	void Attack();

	/// <summary>
	/// 倒された時の処理。
	/// </summary>
	void Death();

	/// <summary>
	/// 見つかった状態にする。
	/// </summary>
	void ChangeStateFound()
	{
		m_enGunEnemyState = enState_found;;
	}

	/// <summary>
	/// プレイヤーのインスタンスを設定。
	/// </summary>
	/// <param name="player">プレイヤーのインスタンス</param>
	void SetPlayer(Player* player)
	{
		m_player = player;
	}
private:
	friend class GunEnemyStateWait;
	friend class GunEnemyStateAttack;
	friend class GunEnemyStateFound;

	IGunEnemyState* m_currentState = nullptr;	//現在のガンエネミーの状態
	GunEnemyStateWait m_gunEnemyStateWait;		//待機状態
	GunEnemyStateAttack m_gunEnemyStateAttack;	//攻撃状態
	GunEnemyStateFound m_gunEnemyStateFound;	//見つかった状態

	SkinModelRender* m_skinModel = nullptr;				//スキンモデル
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度

	enum EnGunEnemyState {
		enState_wait,	//待機状態
		enState_attack,	//攻撃状態
		enState_found	//見つかった状態
	};
	EnGunEnemyState m_enGunEnemyState;	//ガンエネミーの状態

	enum EnAnimationClip {
		enAnim_wait,			//待機アニメーション
		enAnim_attack,			//攻撃アニメーション
		enAnim_found,			//見つかった時のアニメーション
		enAnim_num				//アニメーションクリップの数
	};
	Animation m_animation;					//アニメーション
	AnimationClip m_animClip[enAnim_num];	//アニメーションクリップ
	EnAnimationClip m_enAnimClip;			//アニメーションの状態
	const float m_animTime = 0.2f;			//アニメーション補間時間

	int m_bulletTimer = 0;			//弾を撃つまでの時間
	bool m_foundFlag = false;		//見つかった時の判定
	bool m_sandDustFlag = false;	//砂ぼこりを表示するかどうかのフラグ

	Player* m_player = nullptr;		//プレイヤーのインスタンス

	Effekseer::Effect* m_gunEnemyDeathEffekt = nullptr;			//倒された時のエフェクト
	Effekseer::Effect* m_gunEnemySandDustEffekt = nullptr;		//砂ぼこりのエフェクト
	Effekseer::Handle m_playEffectHandle = -1;
public:
	/// <summary>
	/// 状態を切り替える処理
	/// </summary>
	/// <param name="nextState">ガンエネミーの状態</param>
	void ChangeState(EnGunEnemyState nextState);
};

