#include "stdafx.h"
#include "Stage.h"
#include "IGameObjectManager.h"


Stage::Stage()
{
	//モデルの初期化。
	m_skinModel = g_goMgr.NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/stage_01.cmo");

	//静的オブジェクトを作成。
	m_static.CreateMeshObject(m_skinModel->GetSkinModel(), m_position, m_rotation);

	//シャドウレシーバーを設定
	m_skinModel->SetShadowReciever();
}


Stage::~Stage()
{
	//スキンモデルを削除。
	g_goMgr.DeleteGO(m_skinModel);
}

void Stage::Update()
{
	//シャドウキャスターを設定
	m_skinModel->SetShadowCaster();

	//トゥーンレンダを設定。
	m_skinModel->SetToonRender();

	//スキンモデルの座標を設定。
	m_skinModel->SetPosition(m_position);

	//スキンモデルの回転を設定。
	m_skinModel->SetRotation(m_rotation);
}