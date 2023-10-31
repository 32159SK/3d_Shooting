
/*!
 *  @file       floor.h
 *  @brief      床
 *  @author     Kazuto Shimazaki
 *  @date       2023/05/11
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"

 /*!
  *  @class      CFloor
  *
  *  @brief      ステージクラス
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/05/11
  *
  *  @version    1.0
  */
class CFloor final
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親のオブジェクト
     */
    CFloor(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CFloor(void) = default;

    /*!
     *  @brief      初期化
     */
    void        Initialize(void) override;

    /*!
     *  @brief      描画
     */
    void        Draw(void) override;

    /*!
     *  @brief      解放
     */
    void        Finalize(void) override;

    /*!
     *  @brief  レイキャスト
     */
    void        Raycast(aqua::CVector3 pointA, aqua::CVector3 pointB);

    /*!
     *  @brief  レイキャスト座標取得
     */
    aqua::CVector3 GetRaycastPos(void) { return m_RaycastPos; }

private:
    aqua::CModel            m_Floor;
    aqua::CVector3          m_RaycastPos;   // レイキャスト座標
};
