/*!
 *  @file       unique_life.h
 *  @brief      特殊ライフバークラス
 *  @author     Kazuto Shimazaki
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "../life_bar.h"

 /*!
  *  @class      CUniqueLifeBar
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/08/31
  *
  *  @version    1.0
  */
class CUniqueLifeBar
    : public CLifeBar
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親のオブジェクト
     */
    CUniqueLifeBar(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CUniqueLifeBar(void) = default;

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      更新
     */
    void        Update(void)override;

    /*!
     *  @brief      ライフバー計算処理
     */
    void        CalcLifeBar(void)override;

private:



    std::string m_UnitName;     // ユニット名
};
