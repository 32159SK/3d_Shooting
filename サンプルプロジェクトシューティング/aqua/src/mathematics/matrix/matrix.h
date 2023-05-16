#pragma once
#include<DxLib.h>

namespace aqua
{
	using _Matrix = DxLib::MATRIX;
	using _Vector3 = DxLib::VECTOR;

	class CVector3;

	class CMatrix : public _Matrix
	{
	public:
		CMatrix(void);

		CMatrix(const _Matrix& mat);

		~CMatrix(void) = default;

		void operator=(const _Matrix& mat);

		CMatrix operator+(const _Matrix& mat)const;
		CMatrix& operator+=(const _Matrix& mat);
		CMatrix operator*(const _Matrix& mat)const;
		CMatrix operator*(const float scale)const;
		CMatrix& operator*=(const _Matrix& mat);
		CMatrix operator-(void);

		CMatrix Inverse(void);
		static CMatrix Inverse(const _Matrix& mat);

		CMatrix Transpose(void);
		static CMatrix Transpose(const _Matrix& mat);

		CMatrix& Scale(const _Vector3& scale);

		CMatrix& RotationX(float angle);
		CMatrix& RotationY(float angle);
		CMatrix& RotationZ(float angle);
		CMatrix& RotationAxis(const _Vector3& axis,float angle);

		CVector3 GetRotationXYZ(void);

		CMatrix& Translate(const _Vector3& trans);

		static const CMatrix	INDENT;

	};

}