
/*!
 *  @file       easing.h
 *  @brief      イージング関数
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "..\..\mathematics\mathematics.h"

/*!
 *  @brief  aqua名前空間
 */
namespace aqua
{
    /*!
     *  @brief  aqua::easing名前空間
     */
    namespace easing
    {
        /*!
         *  @brief  線形補間
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float Linear(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InQuad(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float OutQuad(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InOutQuad(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InCubic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float OutCubic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InOutCubic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InQuart(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float OutQuart(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InOutQuart(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InQuintic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float OutQuintic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InOutQuintic(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InSine(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float OutSine(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time   終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InOutSine(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InExp(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time   終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float OutExp(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InOutExp(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InCirc(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float OutCirc(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InOutCirc(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float OutBounce(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InBounce(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         */
        float InOutBounce(float time, float finish_time, float min = 0.0f, float max = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         *  @param[in]  s           係数
         */
        float OutBack(float time, float finish_time, float min = 0.0f, float max = 1.0f, float s = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         *  @param[in]  s           係数
         */
        float InBack(float time, float finish_time, float min = 0.0f, float max = 1.0f, float s = 1.0f);

        /*!
         *  @brief
         *
         *  @param[in]  time        経過時間
         *  @param[in]  finish_time 終了時間
         *  @param[in]  min         最小値
         *  @param[in]  max         最大値
         *  @param[in]  s           係数
         */
        float InOutBack(float time, float finish_time, float min = 0.0f, float max = 1.0f, float s = 1.0f);
    }
}
