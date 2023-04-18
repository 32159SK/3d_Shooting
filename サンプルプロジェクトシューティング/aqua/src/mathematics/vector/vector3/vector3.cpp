
/*!
 *  @file       vector2.cpp
 *  @brief      3�����x�N�g��
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "vector3.h"
#include "..\..\..\debug\debug.h"
#include <cmath>

const aqua::CVector3 aqua::CVector3::ZERO = aqua::CVector3(0.0f, 0.0f,0.0f);
const aqua::CVector3 aqua::CVector3::ONE = aqua::CVector3(1.0f, 1.0f, 1.0f);

/*
 *  �R���X�g���N�^
 */
aqua::CVector3::
CVector3(void)
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

/*
 *  �R���X�g���N�^
 */
aqua::CVector3::
CVector3(float x, float y,float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

/*
 *  �R���X�g���N�^
 */
aqua::CVector3::
CVector3(const aqua::_Vector3& v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

/*
 *  ���K��
 */
aqua::CVector3
aqua::CVector3::
Normalize(void)
{
    return Normalize(*this);
}

/*
 *  ���K��
 */
aqua::CVector3
aqua::CVector3::
Normalize(const _Vector3& v)
{
    CVector3 dxv = VNorm(v);
    if (dxv == -CVector3::ONE) dxv = CVector3::ZERO;
    return dxv;
}

/*
 *  �x�N�g���̑傫���擾
 */
float
aqua::CVector3::
Length(void)
{
    return Length(*this);
}

/*
 *  �x�N�g���̑傫���擾
 */
float
aqua::CVector3::
Length(const _Vector3& v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

/*
 *  ����
 */
float
aqua::CVector3::
Dot(const _Vector3& vA, const _Vector3& vB)
{
    return (vA.x * vB.x + vA.y * vB.y + vA.z * vB.z);
}

aqua::CVector3 
aqua::CVector3::
Cross(const _Vector3& vA, const _Vector3& vB)
{
    return aqua::CVector3((vA.y * vB.z - vA.z * vB.y), (vA.z * vB.x - vA.x * vB.z), (vA.x * vB.y - vA.y * vB.x));
}

/*
 *  �f�o�b�O���O�ɏo�͂���
 */
void
aqua::CVector3::
DebugLog(void)
{
    AQUA_DEBUG_LOG("CVector3(x:" + std::to_string(x) + ", y:" + std::to_string(y) + ", z:"+std::to_string(z)+ ")");
}
