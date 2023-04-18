
/*!
 *  @file       game_object.h
 *  @brief      ゲームオブジェクトベース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include <list>
#include <string>
#include "..\utility\memory\memory.h"

/*!
 *  @brief      aqua名前空間
 */
namespace aqua
{
    /*!
     *  @brief      オブジェクトクラスの前方宣言
     */
    class IGameObject;

    /*!
     *  @brief      オブジェクトクラスリスト型
     */
    typedef std::list<IGameObject*> GAME_OBJECT_LIST;

    /*!
     *  @brief      検索関数登録用関数ポインタ
     */
    typedef bool (*FIND_METHOD)( IGameObject* arg );

    /*!
     *  @brief      ゲームオブジェクト状態ID
     */
    enum class GAME_OBJECT_STATE
    {
        //! 待機(更新なし、描画のみ)
        WAIT,
        //! 更新・描画
        ACTIVE,
        //! 死亡(子オブジェクトもすべて解放)
        DEAD,
    };

    /*!
     *  @class      IGameObject
     *
     *  @brief      ゲームオブジェクトベースクラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class IGameObject
    {
    public:
        /*!
         *  @brief      コンストラクタ
         */
        IGameObject( void );

        /*!
         *  @brief      コンストラクタ
         *
         *  @param[in]  parent  親のオブジェクト
         */
        IGameObject( IGameObject* parent );

        /*!
         *  @brief      コンストラクタ
         *
         *  @param[in]  parent  親のオブジェクト
         *  @param[in]  name    オブジェクト名
         */
        IGameObject( IGameObject* parent, const std::string& name );

        /*!
         *  @brief      コンストラクタ
         *
         *  @param[in]  parent      親のオブジェクト
         *  @param[in]  name        オブジェクト名
         *  @param[in]  category    カテゴリー
         */
        IGameObject( IGameObject* parent, const std::string& name, const std::string& category );

        /*!
         *  @brief      デストラクタ
         */
        virtual ~IGameObject( void ) = default;

        /*!
         *  @brief      初期化
         */
        virtual void        Initialize( void );

        /*!
         *  @brief      更新
         */
        virtual void        Update( void );

        /*!
         *  @brief      描画
         */
        virtual void        Draw( void );

        /*!
         *  @brief      解放
         */
        virtual void        Finalize( void );

        /*!
         *  @brief      親オブジェクトの取得
         *
         *  @return     親のオブジェクト<br>
         *              ルートの場合はnullptr
         */
        IGameObject*        GetParent( void );

        /*!
         *  @brief      子オブジェクトリストの取得
         *
         *  @return     子オブジェクトリスト
         */
        GAME_OBJECT_LIST*   GetChildList( void );

        /*!
         *  @brief      子オブジェクトの追加
         *
         *  @param[in]  obj     子のオブジェクト
         */
        void                AddChild( IGameObject* obj );

        /*!
         *  @brief      子オブジェクトを先頭に追加
         *
         *  @param[in]  obj     子のオブジェクト
         */
        void                AddFrontChild( IGameObject* obj );

        /*!
         *  @brief      子オブジェクトの削除
         *
         *  @param[in]  name    オブジェクトの名前
         *
         *  @return     リストから削除した子のオブジェクト<br>
         *              見つからなかった場合はnullptr
         */
        IGameObject*        RemoveChild( const std::string& name );

        /*!
         *  @brief      子オブジェクトの削除
         *
         *  @param[in]  func    削除条件メソッド
         *
         *  @return     リストから削除した子のオブジェクト<br>
         *              見つからなかった場合はnullptr
         */
        IGameObject*        RemoveChild( FIND_METHOD func );

        /*!
         *  @brief      子のオブジェクト検索
         *
         *  @param[in]  name    オブジェクトの名前
         *
         *  @return     検索オブジェクト<br>
         *              見つからなかった場合はnullptr
         */
        IGameObject*        FindChild( const std::string& name );

        /*!
         *  @brief      子のオブジェクト検索
         *
         *  @param[in]  func    検索条件メソッド
         *
         *  @return     検索オブジェクト<br>
         *              見つからなかった場合はnullptr
         */
        IGameObject*        FindChild( FIND_METHOD func );

        /*!
         *  @brief      兄弟オブジェクト検索
         *
         *  @param[in]  name    オブジェクトの名前
         *
         *  @return     検索オブジェクト<br>
         *              見つからなかった場合はnullptr
         */
        IGameObject*        FindSibling( const std::string& name );

        /*!
         *  @brief      兄弟オブジェクト検索
         *
         *  @param[in]  func    検索条件メソッド
         *
         *  @return     検索オブジェクト<br>
         *              見つからなかった場合はnullptr
         */
        IGameObject*        FindSibling( FIND_METHOD func );

        /*!
         *  @brief      ゲームオブジェクトの削除
         */
        void                DeleteObject( void );

        /*!
         *  @brief      ゲームオブジェクトID取得
         *
         *  @return     ゲームオブジェクトID
         */
        std::string         GetGameObjectName( void ) const;

        /*!
         *  @brief      ゲームオブジェクトカテゴリー取得
         *
         *  @return     ゲームオブジェクトカテゴリー
         */
        std::string         GetGameObjectCategory( void ) const;

        /*!
         *  @brief      ゲームオブジェクト状態取得
         *
         *  @return     ゲームオブジェクト状態
         */
        GAME_OBJECT_STATE   GetGameObjectState( void ) const;

        /*!
         *  @brief      ゲームオブジェクト状態設定
         *
         *  @param[in]  state   ゲームオブジェクト状態
         */
        void                SetGameObjectState( GAME_OBJECT_STATE state );

    protected:
        //! 親のオブジェクト
        IGameObject*                m_ParentObject;
        //! ゲームオブジェクトリスト
        GAME_OBJECT_LIST            m_ChildObjectList;
        //! ゲームオブジェクト名
        std::string                 m_GameObjectName;
        //! ゲームオブジェクトのカテゴリー
        std::string                 m_GameObjectCategory;
        //! ゲームオブジェクト状態
        GAME_OBJECT_STATE           m_GameObjectState;
    };

    /*!
     *  @brief      ゲームオブジェクト生成
     *
     *  @param[in]  parent  親オブジェクト
     *
     *  @return     生成されたゲームオブジェクト
     */
    template <class T>
    T*  CreateGameObject(IGameObject* parent)
    {
        // ゲームオブジェクト生成
        T* t = AQUA_NEW T(parent);

        // 親がいればリストに追加
        if (parent) parent->AddChild(t);

        // オブジェクトの返却
        return t;
    }

    /*!
     *  @brief      ゲームオブジェクト生成
     *
     *  @param[in]  parent  親オブジェクト
     *  @param[in]  name    オブジェクト名
     *
     *  @return     生成されたゲームオブジェクト
     */
    template <class T>
    T*  CreateGameObject(IGameObject* parent, const std::string& name)
    {
        // ゲームオブジェクト生成
        T* t = AQUA_NEW T(parent, name);

        // 親がいればリストに追加
        if (parent) parent->AddChild(t);

        // オブジェクトの返却
        return t;
    }

    /*!
     *  @brief      ゲームオブジェクト生成<br>
     *              子リストの先頭に追加する
     *
     *  @param[in]  parent  親オブジェクト
     *
     *  @return     生成されたゲームオブジェクト
     */
    template <class T>
    T*  CreateGameObjectF(IGameObject* parent)
    {
        // ゲームオブジェクト生成
        T* t = AQUA_NEW T(parent);

        // 親がいればリストに追加
        if (parent) parent->AddFrontChild(t);

        // オブジェクトの返却
        return t;
    }

    /*!
     *  @brief      ゲームオブジェクト生成<br>
     *              子リストの先頭に追加する
     *
     *  @param[in]  parent  親オブジェクト
     *  @param[in]  name    オブジェクト名
     *
     *  @return     生成されたゲームオブジェクト
     */
    template <class T>
    T*  CreateGameObjectF(IGameObject* parent, const std::string& name)
    {
        // ゲームオブジェクト生成
        T* t = AQUA_NEW T(parent, name);

        // 親がいればリストに追加
        if (parent) parent->AddFrontChild(t);

        // オブジェクトの返却
        return t;
    }
}
