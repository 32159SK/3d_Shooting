
/*!
 *  @file       enemy_manager.h
 *  @brief      エネミー管理
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/18
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "enemy/enemy.h"
#include "../ui_component/rader/rader.h"

 /*!
  *  @class      CEnemyManager
  *
  *  @brief      エネミー管理クラス
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/04/18
  *
  *  @version    1.0
  */
class CEnemyManager
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     */
    CEnemyManager(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CEnemyManager(void) = default;

    /*!
     *  @brief      初期化
     */
    void        Initialize(CBulletManager* bm, CPlayer* player, CRader* rader);

    /*!
     *  @brief      更新
     */
    void        Update(void) override;

    /*!
     *  @brief      描画
     */
    void        Draw(void) override;

    /*!
     *  @brief      エネミーの生成
     */
    void        Create(aqua::CVector3 pop_pos, float wid, float hei,float dep,aqua::CColor color);

    /*!
     *  @brief      解放
     */
    void        Finalize(void) override;



private:


    int             m_EnemyCount;

    CPlayer*        m_Player;
    CBulletManager* m_BulletManagar;
    CRader*         m_Rader;
};
