/*!
 *  @file       rader.h
 *  @brief      レーダークラス
 *  @brief      UIコンポーネント
 *  @author     Kazuto Shimazaki
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "../ui_component.h"

 /*!
  *  @class      CRader
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/06/02
  *
  *  @version    1.0
  */
class CSkillIcon
    : public IUIComponent
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親のオブジェクト
     */
    CSkillIcon(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CSkillIcon(void) = default;

    /*!
     *  @brief      初期化
     */
    void        Initialize(CPlayer* player);

    void        Update(void)override;

    /*!
     *  @brief      描画
     */
    void        Draw(void) override;

    /*!
     *  @brief      解放
     */
    void        Finalize(void) override;

    void        SetEnemy(CEnemy* enemy);

private:

    /*!
     *  @brief      レーダー内での表示座標変換
     */
    aqua::CVector2                  SetRaderPos(aqua::CVector2 pos);

    static const std::string        m_unit_path;

    int                             m_EnemyCount;

    aqua::CSprite                   m_RaderSprite;  // レーダー画像
    aqua::CSprite                   m_PlayerSprite; // レーダー内の自機表示
    std::vector<aqua::CSprite>      m_EnemySprite;  // ""のエネミー表示

    aqua::CVector2                  m_RaderSize;    // レーダー画像のサイズ

    CPlayer* m_Player;       // プレイヤー
};
