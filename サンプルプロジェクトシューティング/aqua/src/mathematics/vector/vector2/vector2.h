
/*!
 *  @file       vector2.h
 *  @brief      二次元ベクトル
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

/*!
 *  @brief  aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CVector2
     *
     *  @brief      二次元ベクトルクラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CVector2
    {
    public:
        //! X成分
        float x;
        //! Y成分
        float y;

        /*!
         *  @brief  コンストラクタ
         */
        CVector2( void );

        /*!
         *  @brief  コンストラクタ
         *
         *  @param[in]  x   X成分
         *  @param[in]  y   Y成分
         */
        CVector2( float x, float y );

        /*!
         *  @brief  コンストラクタ
         *
         *  @param[in]  v  ベクトル
         */
        CVector2( const CVector2& v );

        /*!
         *  @brief  デストラクタ
         */
        ~CVector2( void ) = default;

        /*!
         *  @brief      ベクトルの正規化<br>
         *              自身のベクトルも正規化される
         *
         *  @return     正規化されたベクトル
         */
        CVector2            Normalize( void );

        /*!
         *  @brief      ベクトルの正規化
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     正規化されたベクトル
         */
        static CVector2     Normalize( const CVector2& v );

        /*!
         *  @brief      ベクトルの大きさ取得
         *
         *  @return     ベクトルの大きさ
         */
        float               Length( void );

        /*!
         *  @brief      ベクトルの大きさ取得
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルの大きさ
         */
        static float        Length( const CVector2& v );

        /*!
         *  @brief      2つのベクトルの内積<br>
         *              dot = vA・vB
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     内積
         */
        static float        Dot( const CVector2& vA, const CVector2& vB );

        /*!
         *  @brief      2つのベクトルの外積<br>
         *              cross = vA×vB
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     外積
         */
        static float        Cross( const CVector2& vA, const CVector2& vB );

        /*!
         *  @brief      代入演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        CVector2&           operator=( const CVector2& v )
        {
            x = v.x;
            y = v.y;

            return *this;
        }

        /*!
         *  @brief      加算演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        CVector2&           operator+=( const CVector2& v )
        {
            x += v.x;
            y += v.y;

            return *this;
        }

        /*!
         *  @brief      減算演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        CVector2&           operator-=( const CVector2& v )
        {
            x -= v.x;
            y -= v.y;

            return *this;
        }

        /*!
         *  @brief      乗算演算子のオーバーロード
         *
         *  @param[in]  scalar  スカラー値
         *
         *  @return     ベクトルクラス
         */
        CVector2&           operator*=( float scalar )
        {
            x *= scalar;
            y *= scalar;

            return *this;
        }

        /*!
         *  @brief      等価演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     二つのベクトルが等しい
         *  @retval     true    等しい
         *  @retval     false   等しくない
         */
        bool                operator==( const CVector2& v ) const { return (x == v.x && y == v.y); }

        /*!
         *  @brief      不等演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     二つのベクトルが等しくない
         *  @retval     true    等しくない
         *  @retval     false   等しい
         */
        bool                operator!=( const CVector2& v ) const { return (x != v.x || y != v.y); }

        /*!
         *  @brief      正符号演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector2     operator+( const CVector2& v ) { return v; }

        /*!
         *  @brief      負符号演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector2     operator-( const CVector2& v ) { return CVector2(-v.x, -v.y); }

        /*!
         *  @brief      加算演算子のオーバーロード
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector2     operator+(const CVector2& vA, const CVector2& vB) { return aqua::CVector2(vA.x + vB.x, vA.y + vB.y); }

        /*!
         *  @brief      減算演算子のオーバーロード
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector2     operator-(const CVector2& vA, const CVector2& vB) { return CVector2(vA.x - vB.x, vA.y - vB.y); }

        /*!
         *  @brief      乗算演算子のオーバーロード
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector2     operator*(const CVector2& vA, const CVector2& vB) { return CVector2(vA.x * vB.x, vA.y * vB.y); }

        /*!
         *  @brief      乗算演算子のオーバーロード
         *
         *  @param[in]  v       ベクトルクラス
         *  @param[in]  scalar  スカラー値
         *
         *  @return     ベクトルクラス
         */
        friend CVector2     operator*(const CVector2& v, float scalar) { return CVector2(v.x * scalar, v.y * scalar); }

        /*!
         *  @brief      乗算演算子のオーバーロード
         *
         *  @param[in]  scalar  スカラー値
         *  @param[in]  v       ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector2     operator*(float scalar, const CVector2& v) { return CVector2(v.x * scalar, v.y * scalar); }

        /*!
         *  @brief      除算演算子のオーバーロード
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector2     operator/(const CVector2& vA, const CVector2& vB) { return CVector2(vA.x / vB.x, vA.y / vB.y); }

        /*!
         *  @brief      除算演算子のオーバーロード
         *
         *  @param[in]  v       ベクトルクラス
         *  @param[in]  scalar  スカラー値
         *
         *  @return     ベクトルクラス
         */
        friend CVector2     operator/(const CVector2& v, float scalar) { return CVector2(v.x / scalar, v.y / scalar); }

        /*!
         *  @brief      除算演算子のオーバーロード
         *
         *  @param[in]  scalar  スカラー値
         *  @param[in]  v       ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector2     operator/(float scalar, const CVector2& v) { return CVector2(scalar / v.x, scalar / v.y); }

        /*!
         *  @brief      デバッグログに値を表示する
         */
        void                DebugLog( void );

        //! 成分がすべて0のベクトル
        static const CVector2   ZERO;
        //! 成分がすべて1のベクトル
        static const CVector2   ONE;
    };
}
