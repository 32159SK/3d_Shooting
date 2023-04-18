
/*!
 *  @file       vector3.h
 *  @brief      3ŽŸŒ³ƒxƒNƒgƒ‹
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include<DxLib.h>

namespace aqua
{

	class CModel;
	class CVector3;

	class CCollision 
	{
	public:

		bool	collision;

		CCollision(void);

		~CCollision(void) = default;


		virtual bool	CheckCollision(CModel& model);

		virtual bool	CheckCollision(CVector3& pointA, CVector3& pointB);

		virtual bool	CheckCollision(CVector3& center_pos, float r);
	};

};




