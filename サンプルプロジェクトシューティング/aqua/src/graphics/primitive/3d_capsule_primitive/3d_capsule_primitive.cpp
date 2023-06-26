#include "3d_capsule_primitive.h"

aqua::CCapsulePrimitive::CCapsulePrimitive(void)
{
}

void aqua::CCapsulePrimitive::Setup(const aqua::CVector3& A_pos, const aqua::CVector3& B_pos, float r, int divnum, const aqua::CColor& color_, const aqua::CColor& spc_color_, bool fill_)
{
	Apos = A_pos;
	Bpos = B_pos;
	radius = r;
	div_num = divnum;
	color = color_;
	spc_color = spc_color_;
	fill = fill_;
}

void aqua::CCapsulePrimitive::Draw(void)
{
	// 行列を使ってAを中心とした回転処理を行う
	aqua::CMatrix mat;

	mat.RotationZ(aqua::DegToRad(m_TRotate));

	mat.RotationX(aqua::DegToRad(m_VRotate));

	mat.RotationY(aqua::DegToRad(m_HRotate));

	mat.Translate(Apos);

	Bpos *= mat;

	if (!visible) return;

	DrawCapsule3D(Apos, Bpos, radius, div_num, color.GetColor(), spc_color.GetColor(), fill);
}

bool aqua::CCapsulePrimitive::CheckCollision(CVector3& pointA, CVector3& pointB)
{
	return false;
}
