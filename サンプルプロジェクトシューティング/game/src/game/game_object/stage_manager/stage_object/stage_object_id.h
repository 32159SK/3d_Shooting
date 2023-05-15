
/*
 *  @file       stage_object_id.h
 *  @brief      ステージオブジェクトID
 *  @author
 *  @since      1.0
 *
 *  Copyright (c) 2013-2019, Kazuya Maruyama. All rights reserved.
 */

#pragma once

 /*
  *  @brief      ステージオブジェクトID
  */
enum STAGE_OBJECT_ID
{
    NULL_OBJECT,        //!< ブロックなし
    NORMAL_BLOCK,      //!< ノーマルブロック
    BRITTLE_BLOCK,     //!< 破壊可能ブロック
    //MAX              //!< ステージオブジェクト数
};
