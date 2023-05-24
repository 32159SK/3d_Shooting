/*
 *  @file       unit.h
 *  @brief      ユニット処理
 *  @author     Kazuto Shimazaki
 *  @date       2022/06/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../bullet.h"


class CNomalBullet : public IBullet
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    CNomalBullet(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    virtual ~CNomalBullet(void) = default;

    /*
     *  @brief      初期化
     */
    void    Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user)override;


    /*
     *  @brief      更新
     */
    void    Update(void)override;

    void    Draw(void)override;

    void    Finalize(void)override;

private:

    aqua::CModel    m_Model;

};