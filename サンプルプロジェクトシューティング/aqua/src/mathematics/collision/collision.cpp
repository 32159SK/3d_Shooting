#include "collision.h"

aqua::
CCollision::
CCollision(void)
	: collision(false)
{
}

bool aqua::CCollision::CheckCollision(CModel& model)
{
	return false;
}

bool aqua::CCollision::CheckCollision(CVector3& pointA, CVector3& pointB)
{
	return false;
}

bool aqua::CCollision::CheckCollision(CVector3& center_pos, float r)
{
	return false;
}

bool aqua::CCollision::CheckCollision(CVector3& positionA, CVector3& positionB, float r)
{
	return false;
}
