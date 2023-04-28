
/*
 *  @file       game_main.h
 *  @brief      ゲームメインシーン
 *  @author
 *  @date
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include"..\scene.h"


 /*
  *  @class      CGameMain
  *
  *  @brief      ゲームメインシーン
  */
class CGameMain
    : public IScene
{
public:
    /*
     *  @brief      コンストラクタ
     */
    CGameMain(aqua::IGameObject* parent);

    /*
     *  @brief      デストラクタ
     */
    ~CGameMain(void);

    /*
     *  @brief      初期化
     */
    void        Initialize(void);

    /*
     *  @brief      更新
     */
    void        Update(void);

    /*
     *  @brief      描画
     */
    void        Draw(void);

    /*
     *  @brief      解放
     */
    void        Finalize(void);



private:
    /*
     *  @brief      ゲーム開始
     */
    void            GameStart(void);

    /*
     *  @brief      ゲーム中
     */
    void            GamePlay(void);

    /*
     *  @brief      ゲーム終了
     */
    void            GameFinish(void);

    /*
     *  @brief      状態ID
     */
    enum STATE
    {
        STATE_GAME_START,       //! ゲーム開始
        STATE_GAME_PLAY,        //! ゲーム中
        STATE_GAME_FINISH,      //! ゲーム終了
        STATE_GAME_SAVE,        //! スコアのセーブ
    };

    STATE               m_State;        //! 状態ID
    aqua::CCamera       m_Camera;
    CPlayer*            m_Player;
    aqua::CSprite       m_Sprite;
};
