#include "stdafx.h"
#include "Wall.h"

Wall::Wall()
{
	//モデルの初期化。
	m_skinModel = NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/wall.cmo");

	//シャドウレシーバーを設定。
	m_skinModel->SetShadowReciever();
}


Wall::~Wall()
{
	//スキンモデルを削除。
	DeleteGO(m_skinModel);
}

void Wall::Update()
{
	//トゥーンレンダを設定。
	m_skinModel->SetToonRender();

	//スキンモデルの座標を設定。
	m_skinModel->SetPosition(m_position);

	//スキンモデルの回転を設定。
	m_skinModel->SetRotation(m_rotation);
}

void Wall::CreateStaticObject()
{
	//静的オブジェクトを作成。
	m_static.CreateMeshObject(m_skinModel->GetSkinModel(), m_position, m_rotation);
}
