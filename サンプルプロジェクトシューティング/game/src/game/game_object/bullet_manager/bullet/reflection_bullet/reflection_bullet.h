/*
 *  @file       reflect_bullet.h
 *  @brief      反射弾
 *  @author     Kazuto Shimazaki
 *  @date       2022/06/20
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */
#pragma once
#include "aqua.h"
#include "../bullet.h"


class CReflectionBullet : public IBullet
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent          親オブジェクト
     *  @param[in]  object_name     オブジェクト名
     */
    CReflectionBullet(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    virtual ~CReflectionBullet(void) = default;

    /*
     *  @brief      初期化
     */
    void    Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user, CEffectManager* em)override;

    /*
     *  @brief      ステージオブジェクトヒット処理
     */
    void    StageObjectHit(aqua::CCubePrimitive::COLL_DIRE c_dire)override;
private:

    static const int m_max_reflect_count = 3;   // 最大反射回数

    int             m_ReflectCount;             // 反射回数のカウント

};