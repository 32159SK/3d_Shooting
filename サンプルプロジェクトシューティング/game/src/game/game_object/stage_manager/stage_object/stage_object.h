/*
 *  @file       stage_object.h
 *  @brief      ステージオブジェクト
 *  @author
 *  @date
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "stage_object_id.h"

 /*
  *  @class      IStageObject
  *
  *  @brief      ステージオブジェクトクラス
  *
  *  @author     Kazuya Maruyama
  *
  *  @date       2019/11/16
  *
  *  @since      1.0
  */

class CStageManager;

class IStageObject : public aqua::IGameObject
{
public:

    /*
     *  @brief      コンストラクタ
     */
    IStageObject(aqua::IGameObject* parent, const std::string& name);

    /*
     *  @brief      デストラクタ
     */
    virtual ~IStageObject(void);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  id ステージ上のマップチップID
     */
    virtual void        Initialize(const STAGE_OBJECT_ID& id, int x, int y);

    /*
     *  @brief      更新
     */
    virtual void        Update(void);

    /*
     *  @brief      描画
     */
    virtual void        Draw(void);

    /*
     *  @brief      解放
     */
    virtual void        Finalize(void);

    /*
     *  @brief      ステージオブジェクトID取得
     *
     *  @return     ステージオブジェクトID
     */
    STAGE_OBJECT_ID     GetStageObjectID(void) const;


    /*
     *  @brief      ステージオブジェクトID設定
     *
     *  @param[in]  stage_object_id     ステージオブジェクトID
     */
    void                SetStageObjectID(STAGE_OBJECT_ID stage_object_id);
    /*
     *  @brief      位置設定
     *
     *  @param[in]  position    位置
     */
    void                SetPosition(const aqua::CVector3& position);

    /*
     *  @brief      アクティブ状態チェック
     *
     *  @retval     true    アクティブ
     *  @retval     false   非アクティブ
     */
    bool                IsActive(void) const;

    /*
     *  @brief      アクティブフラグ設定
     *
     *  @param[in]  active  アクティブ状態
     */
    void                SetActive(bool active);


    
protected:

    static const float            m_default_size;         //!< 標準サイズ
    STAGE_OBJECT_ID               m_StageObjectID;        //!< ステージオブジェクトID
    aqua::CVector3                m_Position;             //!< 位置
    bool                          m_ActiveFlag;           //!< アクティブフラグ
    bool                          m_CollisionFlag;        //!< 衝突フラグ
    aqua::CCubePrimitive          m_Cube;                 //!< 
};