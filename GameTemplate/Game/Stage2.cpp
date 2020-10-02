#include "stdafx.h"
#include "Stage2.h"
#include "IGameObjectManager.h"

Stage2::Stage2()
{
	//モデルの初期化。
	m_skinModel = g_goMgr.NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/stage_02.cmo");

	//静的オブジェクトを作成。
	m_staticObject.CreateMeshObject(m_skinModel->GetSkinModel(), m_position, m_rotation);

	//シャドウレシーバーを設定。
	m_skinModel->SetShadowReciever();
}

Stage2::~Stage2()
{
	//スキンモデルを削除。
	g_goMgr.DeleteGO(m_skinModel);
}

void Stage2::Update()
{
	//シャドウキャスターを設定。
	m_skinModel->SetShadowCaster();

	//トゥーンレンダーを設定。
	m_skinModel->SetToonRender();

	//スキンモデルの座標を設定。
	m_skinModel->SetPosition(m_position);

	//スキンモデルの回転を設定。
	m_skinModel->SetRotation(m_rotation);
}