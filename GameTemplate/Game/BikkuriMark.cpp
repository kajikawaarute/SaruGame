#include "stdafx.h"
#include "BikkuriMark.h"

BikkuriMark::BikkuriMark()
{
	//モデルの初期化。
	m_skinModel = g_goMgr.NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/Bikkuri_Mark.cmo");
}


BikkuriMark::~BikkuriMark()
{
	//スキンモデルを削除。
	g_goMgr.DeleteGO(m_skinModel);
}

void BikkuriMark::Update()
{
	//トゥーンレンダーを設定。
	m_skinModel->SetToonRender();

	//スキンモデルの座標を設定。
	m_skinModel->SetPosition(m_position);

	//スキンモデルの回転を設定。
	m_skinModel->SetRotation(m_rotation);
}