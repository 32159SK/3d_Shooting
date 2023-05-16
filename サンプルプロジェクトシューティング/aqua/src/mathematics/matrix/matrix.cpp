#include "matrix.h"
#include "../vector/vector.h"
#include <cmath>

namespace aqua
{
	const CMatrix CMatrix::INDENT = MGetIdent();


	CMatrix::CMatrix(void)
	{
		(*this) = CMatrix::INDENT;
	}

	CMatrix::CMatrix(const _Matrix& mat)
	{
		(*this) = mat;
	}

	void CMatrix::operator=(const _Matrix& mat)
	{
		for (int w = 0; w < 4; ++w)
			for (int h = 0; h < 4; ++h)
				m[w][h] = mat.m[w][h];
	}

	CMatrix CMatrix::operator+(const _Matrix& mat) const
	{
		return MAdd(*this, mat);
	}

	CMatrix& CMatrix::operator+=(const _Matrix& mat)
	{
		(*this) = (*this) + mat;
		return (*this);
	}

	CMatrix CMatrix::operator*(const _Matrix& mat) const
	{
		return MMult(*this, mat);
	}

	CMatrix CMatrix::operator*(const float scale) const
	{
		return MScale(*this, scale);
	}

	CMatrix& CMatrix::operator*=(const _Matrix& mat)
	{
		(*this) = (*this) * mat;
		return (*this);
	}

	CMatrix CMatrix::operator-(void)
	{
		return Inverse(*this);
	}

	CMatrix CMatrix::Inverse(void)
	{
		return Inverse(*this);
	}

	CMatrix CMatrix::Inverse(const _Matrix& mat)
	{
		return MInverse(mat);
	}

	CMatrix CMatrix::Transpose(void)
	{
		return Transpose(*this);
	}

	CMatrix CMatrix::Transpose(const _Matrix& mat)
	{
		return MTranspose(mat);
	}

	CMatrix& CMatrix::Scale(const _Vector3& scale)
	{
		(*this) *= MGetScale(scale);
		return (*this);
	}

	CMatrix& CMatrix::RotationX(float angle)
	{
		(*this) *= MGetRotX(angle);
		return (*this);
	}

	CMatrix& CMatrix::RotationY(float angle)
	{
		(*this) *= MGetRotY(angle);
		return (*this);
	}

	CMatrix& CMatrix::RotationZ(float angle)
	{
		(*this) *= MGetRotZ(angle);
		return (*this);
	}

	CMatrix& CMatrix::RotationAxis(const _Vector3& axis, float angle)
	{
		(*this) *= MGetRotAxis(axis, angle);
		return (*this);
	}

	CVector3 CMatrix::GetRotationXYZ(void)
	{
		CVector3 v = CVector3::ZERO;

		v.x = atan2f(m[2][1], m[2][2]);
		v.y = asinf(-m[2][0]);
		v.z = atan2f(m[1][0], m[0][0]);

		return v;
	}

	CMatrix& CMatrix::Translate(const _Vector3& trans)
	{
		(*this) *= MGetTranslate(trans);
		return (*this);
	}

}
