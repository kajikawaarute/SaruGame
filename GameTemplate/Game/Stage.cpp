#include "stdafx.h"
#include "Stage.h"
#include "level/Level.h"
#include "IGameObjectManager.h"
#include "Player.h"
#include "Saru.h"
#include "Enemy.h"
#include "JumpFloor.h"
#include "graphics/ShadowMap.h"
#include "graphics/ToonRender.h"

Stage::Stage()
{
	m_model.Init(L"Assets/modelData/stage_01.cmo");
	m_static.CreateMeshObject(m_model, m_position, m_rotation);

	//シャドウレシーバーを設定
	m_model.SetShadowReciever(true);
}


Stage::~Stage()
{
}

void Stage::Update()
{
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);

	//シャドウキャスターを設定
	ShadowMap::GetInstance().RegistShadowCaster(&m_model);

	//トゥーンレンダを設定。
	ToonRender::GetInstance().RegistToonRender(&m_model);
}

void Stage::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}