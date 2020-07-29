#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"


GameCamera::GameCamera()
{
	/*g_camera3D.SetPosition({ 0.0f, 100.0f, -300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);*/

	m_toCameraPos.Set(0.0f, 250.0f, -500.0f);
	g_camera3D.SetNear(10.0f);
	g_camera3D.SetFar(30000.0f);
}


GameCamera::~GameCamera()
{
}

void GameCamera::Update()
{
	//注視点
	CVector3 Target = pl->GetPos();
	Target.y += 50.0f;

	//Rスティックでカメラを回す
	CVector3 toCameraPosOld = m_toCameraPos;
	float x = g_pad[0].GetRStickXF();
	float y = g_pad[0].GetRStickYF();

	//Y軸周り
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 4.0f * x);
	qRot.Multiply(m_toCameraPos);

	//X軸周り
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 4.0f * y);
	qRot.Multiply(m_toCameraPos);

	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8) {
		m_toCameraPos = toCameraPosOld;
	}

	//視点
	CVector3 Position = Target + m_toCameraPos;

	g_camera3D.SetTarget(Target);
	g_camera3D.SetPosition(Position);
	g_camera3D.Update();
}

void GameCamera::Draw()
{
}
