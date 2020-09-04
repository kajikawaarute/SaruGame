#include "stdafx.h"
#include "BikkuriMark.h"
#include "IGameObjectManager.h"
#include "graphics/ToonRender.h"

BikkuriMark::BikkuriMark()
{
	//モデルの初期化。
	m_model.Init(L"Assets/modelData/Bikkuri_Mark.cmo");
}


BikkuriMark::~BikkuriMark()
{
}

void BikkuriMark::Update()
{
	//トゥーンレンダーを設定。
	ToonRender::GetInstance().RegistToonRender(&m_model);

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void BikkuriMark::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
