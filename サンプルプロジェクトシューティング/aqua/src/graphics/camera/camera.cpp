#include "camera.h"

/*
 *  �R���X�g���N�^
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
 *  �J�����̃Z�b�g
 */
void
aqua::CCamera::
SetCamera(float ne, float fa)
{
	m_Near = ne;
	m_Far = fa;
	// �J�����̎�O�N���b�v�����Ɖ��N���b�v������ݒ肷��
	SetCameraNearFar(m_Near, m_Far);
}

/*
 *  �J�����̃Z�b�g
 */
void
aqua::CCamera::
SetCamera(float ne, float fa, aqua::CVector3 pos, aqua::CVector3 tag)
{
	SetCamera(ne, fa);
	m_Position = pos;
	m_Target = tag;
	// �J�����̎��_�A�����_��ݒ肷��( ������͂x������Z�o )
	SetCameraPositionAndTarget_UpVecY(m_Position, m_Target);
}

/*
 *  �J�����̃Z�b�g
 */
void 
aqua::CCamera::
SetCamera(float ne, float fa, aqua::CVector3 pos, aqua::CVector3 tag, aqua::CVector3 up)
{
	SetCamera(ne, fa);
	m_Position = pos;
	m_Target = tag;
	m_CameraUp = up;
	// �J�����̎��_�A�����_�A�������ݒ肷��
	SetCameraPositionAndTargetAndUpVec(m_Position, m_Target, m_CameraUp);
}

void aqua::CCamera::SetCamera(void)
{
	SetCameraPositionAndTarget_UpVecY(m_Position, m_Target);
}

/*
 *  �p�x�̕ύX
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
	// �J�����̎��_�A������]�p�x�A������]�p�x�A�P���]�p�x��ݒ肷��
	SetCameraPositionAndAngle(m_Position, m_VRotate, m_HRotate, m_TRotate);
}
