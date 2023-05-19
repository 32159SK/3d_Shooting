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
  *  @author     
  *
  *  @date       
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
    ~IStageObject(void) = default;

    /*!
     *  @brief      初期化
     *
     *  @param[in]  id ステージ上のマップチップID
     */
    virtual void        Initialize(const STAGE_OBJECT_ID& id, int x, int z);

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


    virtual bool        CollisionCheck(aqua::CVector3 position, aqua::CVector3 destination);

protected:

    virtual void        GoIn(void);

    virtual void        GoOut(void);

    // ステージオブジェクトの状態
    enum OBJECT_STATE
    {
        GO_IN,
        PLAY,
        GO_OUT,
        FINISH
    };

    static const float            m_default_size;         //!< 標準サイズ
    static const float            m_transition_time;      //!< オブジェクトの遷移時間
    STAGE_OBJECT_ID               m_StageObjectID;        //!< ステージオブジェクトID
    OBJECT_STATE                  m_ObjectState;
    aqua::CVector3                m_Position;             //!< 位置
    aqua::CTimer                  m_Timer;                //!< オブジェクトの遷移タイマー
    bool                          m_ActiveFlag;           //!< アクティブフラグ
    bool                          m_CollisionFlag;        //!< 衝突フラグ


};