
/*!
 *  @file       draw_object.h
 *  @brief      描画オブジェクト登録用インターフェース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @brief      aqua::core名前空間
     */
    namespace core
    {
        class CGraphicsDevice;

        /*!
         *  @class      IDrawObject
         *
         *  @brief      描画オブジェクト登録用インターフェイスクラス
         *
         *  @author     Kazuya Maruyama
         *
         *  @date       2021/03/10
         *
         *  @version    7.17
         */
        class IDrawObject
        {
        public:
            //! 可視フラグ
            bool    visible;

        protected:
            /*!
             *  @brief      コンストラクタ
             */
            IDrawObject( void );

            /*!
             *  @brief      デストラクタ
             */
            virtual ~IDrawObject( void ) = default;

            /*!
             *  @brief      更新インターフェイス
             */
            virtual void    Update( void );

            /*!
             *  @brief      描画インターフェイス
             */
            virtual void    Draw( void );
        };
    }
}
