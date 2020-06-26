#include "stdafx.h"
#include "Stage.h"
#include "level/Level.h"
#include "IGameObjectManager.h"
#include "Player.h"
#include "Saru.h"
#include "Enemy.h"
#include "JumpFloor.h"
#include "ShadowMap.h"

Stage::Stage()
{
	m_model.Init(L"Assets/modelData/stage_01.cmo");
	m_static.CreateMeshObject(m_model, m_position, m_rotation);
}


Stage::~Stage()
{
}

void Stage::Update()
{
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	ShadowMap::GetInstance().RegistShadowCaster(&m_model);
}

void Stage::Draw()
{
	m_model.Draw(
		enRenderMode_Normal,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}