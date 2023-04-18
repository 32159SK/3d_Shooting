
/*!
 *  @file       camera_control.h
 *  @brief      カメラ管理
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/11
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */
#pragma once

#include "aqua.h"

/*!
 *  @class      CCameraControl
 *
 *  @brief      カメラコントロールクラス
 *
 *  @author     Kazuto Shimazaki
 *
 *  @date       2023/04/11
 *
 *  @version    1.0
 */
class CCameraControl
{
public:

    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  camera  カメラオブジェクト
     */
    CCameraControl(aqua::CCamera* camera);

    /*!
     *  @brief      デストラクタ
     */
    ~CCameraControl(void) = default;

    /*!
     *  @brief      カメラ移動
     */
    void            Move(void);

    /*!
     *  @brief      カメラ操作
     */
    void            Operation(void);

private:
	aqua::CCamera*	m_Camera;
    aqua::CVector3  m_Velocity;     // カメラの移動速度
    float           m_CamSpeed;     // カメラ移動の速さ
};