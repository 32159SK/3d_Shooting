
/*!
 *  @file       data_relay.h
 *  @brief      中継クラス
 *  @author
 *  @date
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include <stdio.h>
#include <string>


/*!
 *  @class      CDataRelay
 *
 *  @brief      中継クラス
 *
 *  @author
 *
 *  @date
 *
 *  @version    1.0
 */
class CDataRelay
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     */
    CDataRelay(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CDataRelay(void) = default;


    /*!
     *  @brief      リザルト時に扱うデータ取得
     */
    void    SetClear(bool clear) { m_Clear = clear; }


    /*!
     *  @brief      リザルト時に扱うデータ取得
     */
    bool    GetClearFlag(void) { return m_Clear; }
private:

    bool            m_Clear;        // 
};
