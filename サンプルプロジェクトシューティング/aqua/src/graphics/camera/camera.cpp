#include "camera.h"

/*
 *  コンストラクタ
 */
aqua::CCamera::
CCamera(void)
	: m_Near(0)
	, m_Far(0)
	, m_Fov(0)
	, m_VRotate(0)
	, m_HRotate(0)
	, m_TRotate(0)
	, m_Position(aqua::CVector3::ZERO)
	, m_Target(aqua::CVector3::ZERO)
	, m_CameraUp(aqua::CVector3::ZERO)
{
}

/*
 *  カメラのセット
 */
void
aqua::CCamera::
SetCamera(float ne, float fa)
{
	m_Near = ne;
	m_Far = fa;
	// カメラの手前クリップ距離と奥クリップ距離を設定する
	SetCameraNearFar(m_Near, m_Far);
}

/*
 *  カメラのセット
 */
void
aqua::CCamera::
SetCamera(float ne, float fa, aqua::CVector3 pos, aqua::CVector3 tag)
{
	SetCamera(ne, fa);
	m_Position = pos;
	m_Target = tag;
	// カメラの視点、注視点を設定する( 上方向はＹ軸から算出 )
	SetCameraPositionAndTarget_UpVecY(m_Position, m_Target);
}

/*
 *  カメラのセット
 */
void 
aqua::CCamera::
SetCamera(float ne, float fa, aqua::CVector3 pos, aqua::CVector3 tag, aqua::CVector3 up)
{
	SetCamera(ne, fa);
	m_Position = pos;
	m_Target = tag;
	m_CameraUp = up;
	// カメラの視点、注視点、上方向を設定する
	SetCameraPositionAndTargetAndUpVec(m_Position, m_Target, m_CameraUp);
}

void aqua::CCamera::SetCamera(void)
{
	SetCameraPositionAndTarget_UpVecY(m_Position, m_Target);
}

/*
 *  角度の変更
 */
void
aqua::CCamera::
SetAngle(ANGLE angle, float rad)
{
	switch (angle)
	{
	case aqua::V:
		m_VRotate = rad;
		break;
	case aqua::H:
		m_HRotate = rad;
		break;
	case aqua::T:
		m_TRotate = rad;
		break;
	}
	// カメラの視点、垂直回転角度、水平回転角度、捻り回転角度を設定する
	SetCameraPositionAndAngle(m_Position, m_VRotate, m_HRotate, m_TRotate);
}
