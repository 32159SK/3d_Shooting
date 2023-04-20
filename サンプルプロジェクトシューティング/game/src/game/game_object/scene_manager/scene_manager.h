
/*
 *  @file       scene_manager.h
 *  @brief      シーン管理
 *  @author     Kazuto Shimazaki
 *  @date       2023/04/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "scene\scene_id.h"
 /*
  *  @class      CSceneManager
  *
  *  @brief      シーン管理クラス
  *
  *  @author
  *
  *  @date
  *
  *  @version    1.0
  */
class CSceneManager
    : public aqua::IGameObject
{
public:
    /*
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親オブジェクト
     */
    CSceneManager(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    ~CSceneManager(void) = default;

    /*
     *  @brief      初期化
     */
    void        Initialize(void) override;

    /*
     *  @brief      更新
     */
    void        Update(void) override;

    /*
     *  @brief      描画
     */
    void        Draw(void) override;

    /*
     *  @brief      解放
     */
    void        Finalize(void) override;

    /*
     *  @brief      シーンの変更
     *
     *  @param[in]  id  シーンID
     */
    void        Change(SCENE_ID id);

    /*
     *  @brief      シーンをスタックする
     *
     *  @param[in]  id  シーンID
     */
    void        Push(SCENE_ID id);

    /*
     *  @brief      スタックしたシーンを取り出す
     */
    void        Pop(void);

    /*
     *  @brief      現在のシーンをリセットする
     */
    void        Reset(void);

private:
    /*
     *  @brief      状態ID
     */
    enum class STATE
    {
        SCENE_IN,         //! 開始
        SCENE_UPDATA,     //! 更新
        SCENE_OUT,        //! 終了
        SCENE_CHANGE,     //! 変更
    };

    /*
     *  @brief      シーンの生成
     *
     *  @param[in]  id  シーンID
     */
    void        Create(SCENE_ID id);

    /*
     *  @brief      現在のシーンを削除
     */
    void        Delete(void);

    /*
     *  @brief      シーン開始演出
     */
    void        SceneIn(void);

    /*
     *  @brief      シーン更新
     */
    void        SceneUpdate(void);

    /*
     *  @brief      シーン終了演出
     */
    void        SceneOut(void);

    /*
     *  @brief      シーン変更
     */
    void        SceneChange(void);

    static const float  m_fade_speed;       //! フェード速度
    SCENE_ID            m_CurrentSceneID;   //! 現在のシーンID
    SCENE_ID            m_NextSceneID;      //! 次のシーンID
    SCENE_ID            m_PushSceneID;      //! プッシュするシーンID
    STATE               m_State;            //! 状態ID
    bool                m_PushFlag;         //! シーンのプッシュが行われた
    aqua::CSprite       m_FadeSprite;       //! フェード用スプライト
};
