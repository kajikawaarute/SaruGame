#pragma once
#include "IGameObject.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"

class SkinModelRender : public IGameObject
{
public:
	SkinModelRender();
	~SkinModelRender();

	/// <summary>
	/// スキンモデルレンダーの更新関数
	/// </summary>
	void Update();

	/// <summary>
	/// スキンモデルレンダーの描画関数
	/// </summary>
	void Draw();

	/// <summary>
	/// モデルの初期化。
	/// </summary>
	/// <param name="filePath">モデルのファイルパス</param>
	void Init(const wchar_t* filePath);

	/// <summary>
	/// シャドウキャスターを設定。
	/// キャスターは影を落とす側。
	/// </summary>
	void SetShadowCaster()
	{
		ShadowMap::GetInstance().RegistShadowCaster(&m_model);
	}

	/// <summary>
	/// シャドウレシーバーを設定。
	/// レシーバーは影を落とされる側。
	/// </summary>
	void SetShadowReciever()
	{
		m_model.SetShadowReciever(true);
	}

	/// <summary>
	/// トゥーンレンダリングを設定。
	/// </summary>
	void SetToonRender()
	{
		ToonRender::GetInstance().RegistToonRender(&m_model);
	}

	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(const CQuaternion rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// スキンモデルを取得。
	/// </summary>
	/// <returns>スキンモデル</returns>
	SkinModel& GetSkinModel()
	{
		return m_model;
	}
private:
	SkinModel m_model;									//モデル
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_scale = CVector3::One();					//拡大率
};

