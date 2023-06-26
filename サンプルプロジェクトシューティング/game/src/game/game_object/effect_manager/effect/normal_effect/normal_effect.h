
/*!
 *  @file       hit_effect.h
 *  @brief      通常エフェクトクラス
 *  @author     Kazuto Shimazaki
 *  @date       2023/06/19
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\effect.h"

 /*!
  *  @class      CNormalEffect
  *
  *  @brief      通常エフェクトクラス
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/06/19
  *
  *  @version    1.0
  */
class CNormalEffect
    : public IEffect
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親のオブジェクト
     */
    CNormalEffect(IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CNormalEffect(void) = default;

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
     */
    void    Initialize(const aqua::CVector3& position, std::string effect_name, std::string se_name,float rotate = 0.0f)override;

    /*!
     *  @brief      更新
     */
    void    Update(void)override;

    /*!
     *  @brief      描画
     */
    void    Draw(void)override;

    /*!
     *  @brief      解放
     */
    void    Finalize(void)override;


private:
    aqua::CEffect3D     m_Effect;
    float               m_Rotate;
};
