#include "stdafx.h"
#include "Saru.h"


Saru::Saru()
{
	m_model.Init(L"Assets/modelData/Saru.cmo");
	m_animClip[enAnim_taiki].Load(L"Assets/animData/Saru-run.tka");
	m_animClip[enAnim_taiki].SetLoopFlag(true);

	m_animation.Init(m_model, m_animClip, enAnim_num);
	m_position.z = 500.0f;
}

Saru::~Saru()
{
}

void Saru::Update()
{
	m_animation.Update(1.0f / 30.0f);
	m_animation.Play(enAnim_taiki);

	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void Saru::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
