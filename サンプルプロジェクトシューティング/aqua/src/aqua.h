
/*!
 *  @file       aqua.h
 *  @brief      AQUA Game Library
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <windows.h>
#include <DxLib.h>
#include <string>
#include <list>
#include <vector>
#include "controls\controls.h"
#include "debug\debug.h"
#include "framework\framework.h"
#include "game_object\game_object.h"
#include "graphics\graphics.h"
#include "mathematics\mathematics.h"
#include "sounds\sounds.h"
#include "utility\utility.h"
#include "videos\videos.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @brief      AQUA Game Library起動/実行
     *              使用する際に必ず呼び出すこと。
     *
     *  @param[in]  instance_handle     インスタンスハンドル
     *  @param[in]  game                ゲームクラス
     */
    void                Setup( HINSTANCE instance_handle, aqua::IGameObject* game );

    /*!
     *  @brief      インスタンスハンドルの取得
     *
     *  @return     インスタンスハンドル
     */
    HINSTANCE           GetInstanceHandle( void );

    /*!
     *  @brief      ウィンドウハンドルの取得
     *
     *  @return     ウィンドウハンドル
     */
    HWND                GetWindowHandle( void );

    /*!
     *  @brief      ウィンドウの横幅取得
     *
     *  @return     ウィンドウの横幅
     */
    unsigned int        GetWindowWidth( void );

    /*!
     *  @brief      ウィンドウの縦幅取得
     *
     *  @return     ウィンドウの縦幅
     */
    unsigned int        GetWindowHeight( void );

    /*!
     *  @brief      デルタタイム取得
     *
     *  @return     デルタタイム
     */
    float               GetDeltaTime( void );

    /*!
     *  @brief      デルタタイム(タイムスケールなし)取得
     *              デルタタイムは前回の更新からどれくらいの時間が経過したかの値
     *
     *  @return     デルタタイム
     */
    float               GetUnscaledDeltaTime( void );

    /*!
     *  @brief      デルタタイム倍率取得
     *
     *  @return     デルタタイム倍率
     */
    float               GetDeltaTimeScale( void );

    /*!
     *  @brief      デルタタイム倍率設定
     *
     *  @param[in]  scale   デルタタイム倍率
     */
    void                SetDeltaTimeScale( float scale );

    /*!
     *  @brief      フレームレート設定
     *
     *  @param[in]  frame_rate  フレームレート
     */
    void                SetFrameRate( int frame_rate );

    /*!
     *  @brief      ゲームオブジェクトの検索
     *
     *  @param[in]  name    オブジェクト名
     *
     *  @return     検索オブジェクト<br>
     *              見つからなかった場合はNULL
     */
    aqua::IGameObject*  FindGameObject( const std::string& name );

    /*!
     *  @brief      ゲームオブジェクトの検索
     *
     *  @param[in]  func    検索条件メソッド
     *
     *  @return     検索オブジェクト<br>
     *              見つからなかった場合はNULL
     */
    aqua::IGameObject*  FindGameObject( aqua::FIND_METHOD func );

    /*!
     *  @brief      画面のクリア
     *
     *  @param[in]  color   クリアカラー
     */
    void                Clear( unsigned int color );
}
