#include "stdafx.h"
#include "Sky.h"

Sky::Sky()
{
	//モデルの初期化。
	m_skinModel = NewGO<SkinModelRender>();
	m_skinModel->Init(L"Assets/modelData/SkyBox.cmo");
}

Sky::~Sky()
{
	//スキンモデルを削除。
	DeleteGO(m_skinModel);
}

void Sky::Update()
{
	//スキンモデルの座標を設定。
	m_skinModel->SetPosition(m_position);

	//スキンモデルの回転を設定。
	m_skinModel->SetRotation(m_rotation);
}
