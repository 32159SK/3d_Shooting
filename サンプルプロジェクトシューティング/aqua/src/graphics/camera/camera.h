
/*!
 *  @file       camera.h
 *  @brief      カメラ
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include<DxLib.h>
#include"../../mathematics/vector/vector.h"

namespace aqua
{

    /*!
     *  @brief      角度の向き
     */
    enum ANGLE
    {
        V,          //! 垂直方向 
        H,          //! 水平方向
        T           //! 捻り方向
    };


    /*!
     *  @class      CCamera
     *
     *  @brief      カメラ
     *
     *  @author     Kazuto Shimazaki
     *
     *  @date       2023/04/10
     *
     *  @version    7.17
     */
    class CCamera
    {
    public:
        //! 手前クリップ距離
        float           m_Near;
        //! 奥クリップ距離
        float           m_Far;
        //! 視野角
        float           m_Fov;
        //! 垂直回転角度
        float           m_VRotate;
        //! 水平回転角度
        float           m_HRotate;
        //! 捻り回転角度
        float           m_TRotate;
        //! 注視点からカメラまでの距離
        float           m_Distace;
        //! カメラの位置
        aqua::CVector3  m_Position;
        //! カメラの注視点(見ている座標)
        aqua::CVector3  m_Target;
        //! カメラの上方向
        aqua::CVector3  m_CameraUp;

        /*!
         *  @brief  コンストラクタ
         */
        CCamera(void);

        /*!
         *  @brief      デストラクタ
         */
        ~CCamera(void) = default;

        /*!
         *  @brief  カメラのセット
         *
         *  @param[in]  ne    手前
         *  @param[in]  fa    奥
         */
        void SetCamera(float ne,float fa);

        /*!
         *  @brief  カメラのセット
         *
         *  @param[in]  ne    手前
         *  @param[in]  fa    奥
         *  @param[in]  pos   位置
         *  @param[in]  tag   注視点
         */
        void SetCamera(float ne, float fa, aqua::CVector3 pos, aqua::CVector3 tag);

        /*!
         *  @brief  カメラのセット
         *
         *  @param[in]  ne    手前
         *  @param[in]  fa    奥
         *  @param[in]  pos   位置
         *  @param[in]  tag   注視点
         *  @param[in]  up    上方向
         */
        void SetCamera(float ne, float fa, aqua::CVector3 pos, aqua::CVector3 tag, aqua::CVector3 up);

        /*!
         *  @brief  カメラのセット(引数無)
         */
        void SetCamera(void);

        /*!
         *  @brief      角度の変更
         * 
         *  @param[in]  angle  変更する角度の向き
         *  @param[in]  rad    角度の大きさ
         */
        void        SetAngle(ANGLE angle, float rad);


        void        Update(void);

    };

}