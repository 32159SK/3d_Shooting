/*!
 *  @file       life_bar.h
 *  @brief      ライフバークラス
 *  @author     Kazuto Shimazaki
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "../ui_component.h"

 /*!
  *  @class      CLifeBar
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/06/05
  *
  *  @version    1.0
  */
class CLifeBar
    : public IUIComponent
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親のオブジェクト
     */
    CLifeBar(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CLifeBar(void) = default;

    /*!
     *  @brief      初期化
     */
    void                Initialize(void);

    /*!
     *  @brief      更新
     */
    void                Update(void)override;

    /*!
     *  @brief      描画
     */
    void                Draw(void) override;

    /*!
     *  @brief      解放
     */
    void                Finalize(void) override;

    /*!
     *  @brief      ライフバー計算処理
     */
    virtual void        CalcLifeBar(void);

    /*!
     *  @brief      座標取得
     */
    aqua::CVector2      GetFramePosition(void) { return m_Sprite[0].position; }

protected:


    aqua::CSprite                   m_Sprite[2];// 

    aqua::CCamera*                  m_Camera;   // カメラのポインタ容器

    IUnit*                          m_Unit;

    CGameMain*                      m_GameMain; // ゲームメインシーンのポインタ容器
};
