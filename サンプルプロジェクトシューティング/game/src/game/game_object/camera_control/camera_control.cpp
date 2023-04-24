#include "camera_control.h"
#include <algorithm>


CCameraControl::CCameraControl(aqua::CCamera* camera)
	: m_Velocity(aqua::CVector3::ZERO)
	, m_CamSpeed(1.0f)
{
	m_Camera = camera;
}


void CCameraControl::Move(void)
{
	using namespace aqua::keyboard;
	const float to_delta = 60.0f * aqua::GetDeltaTime();

	aqua::CVector3 dir = m_Camera->m_Target - m_Camera->m_Position;

	aqua::CVector3 up = aqua::CVector3(0.0f, 1.0f, 0.0f);

	aqua::CVector3 cam_front = dir;

	cam_front.y = 0.0f;
	cam_front = cam_front.Normalize();

	aqua::CVector3 cam_left = aqua::CVector3::Cross(cam_front, up);
	cam_left = cam_left.Normalize();

	m_Velocity = aqua::CVector3::ZERO;

	if (Button(KEY_ID::W)) m_Velocity += cam_front;
	if (Button(KEY_ID::S)) m_Velocity -= cam_front;
	if (Button(KEY_ID::A)) m_Velocity += cam_left;
	if (Button(KEY_ID::D)) m_Velocity -= cam_left;

	m_Velocity = m_Velocity.Normalize();
	m_Velocity *= (m_CamSpeed * to_delta);

	const float yaw_pitch_speed = 3.0f;
	const float max_pitch = 70.0f;

	bool key_left = Button(KEY_ID::LEFT);
	bool key_right = Button(KEY_ID::RIGHT);
	bool key_up = Button(KEY_ID::UP);
	bool key_down = Button(KEY_ID::DOWN);

	aqua::CMatrix rot_mat;

	// ƒJƒƒ‰Šp“x‚Ì‘€ì
	if (key_left || key_right || key_up || key_down)
	{
		float yaw = key_right ? yaw_pitch_speed : 0.0f;
		yaw += key_left ? -yaw_pitch_speed : 0.0f;
		float pitch = key_up ? -yaw_pitch_speed : 0.0f;
		pitch += key_down ? yaw_pitch_speed : 0.0f;

		pitch = std::clamp(pitch, -max_pitch, max_pitch);

		rot_mat.RotationAxis(cam_left, aqua::DegToRad(pitch * to_delta));
		rot_mat.RotationY(aqua::DegToRad(yaw * to_delta));

	}

	dir *= rot_mat;


	m_Camera->m_Position += m_Velocity;
	m_Camera->m_Target = m_Camera->m_Position + dir;

	m_Camera->SetCamera();

}

