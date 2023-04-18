#include "3d_sphere_primitive.h"

aqua::CSpherePrimitive::CSpherePrimitive(void)
{
}

void aqua::CSpherePrimitive::Setup(const aqua::CVector3& position_, float r, int divnum, const aqua::CColor& color_, const aqua::CColor& spc_color_, bool fill_)
{
	position = position_;
	radius = r;
	div_num = divnum;
	color = color_;
	spc_color = spc_color_;
	fill = fill_;
}

void aqua::CSpherePrimitive::Draw(void)
{
	if (!visible) return;

	DrawSphere3D(position, radius,div_num, color.GetColor(), spc_color.GetColor(), fill);
}

bool aqua::CSpherePrimitive::CheckCollision(CVector3& pointA, CVector3& pointB)
{
	return false;
}
