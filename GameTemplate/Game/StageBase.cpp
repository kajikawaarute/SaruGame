#include "stdafx.h"
#include "StageBase.h"

StageBase::StageBase()
{
}
bool StageBase::Start()
{
	//モデルの初期化。
	m_skinModel = g_goMgr.NewGO<SkinModelRender>();
	m_skinModel->Init(GetCMOFilePath());

	//静的オブジェクトを作成。
	m_staticObject.CreateMeshObject(m_skinModel->GetSkinModel(), m_position, m_rotation);

	//シャドウレシーバーを設定。
	m_skinModel->SetShadowReciever();
	return true;
}
StageBase::~StageBase()
{
	//スキンモデルを削除。
	g_goMgr.DeleteGO(m_skinModel);
}

void StageBase::Update()
{
	//シャドウキャスターを設定。
	m_skinModel->SetShadowCaster();

	//トゥーンレンダーを設定。
	m_skinModel->SetToonRender();

	//スキンモデルの座標を設定。
	m_skinModel->SetPosition(m_position);

	//スキンモデルの回転を設定。
	m_skinModel->SetRotation(m_rotation);

	//ステージ固有の更新処理。
	LocalUpdate();
}
