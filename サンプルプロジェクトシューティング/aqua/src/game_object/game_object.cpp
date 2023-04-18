
/*!
 *  @file       game_object.cpp
 *  @brief      ゲームオブジェクトベース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "game_object.h"

/*
 *  コンストラクタ
 */
aqua::IGameObject::
IGameObject( void )
    : m_ParentObject( nullptr )
    , m_GameObjectName( "None" )
    , m_GameObjectCategory( "None" )
    , m_GameObjectState( GAME_OBJECT_STATE::ACTIVE )
{
    m_ChildObjectList.clear( );
}

/*
 *  コンストラクタ
 */
aqua::IGameObject::
IGameObject( IGameObject* parent )
    : m_ParentObject( parent )
    , m_GameObjectName( "None" )
    , m_GameObjectCategory( "None" )
    , m_GameObjectState( GAME_OBJECT_STATE::ACTIVE )
{
    m_ChildObjectList.clear( );
}

/*
 *  コンストラクタ
 */
aqua::IGameObject::
IGameObject( IGameObject* parent, const std::string& name )
    : m_ParentObject( parent )
    , m_GameObjectName( name )
    , m_GameObjectCategory( "None" )
    , m_GameObjectState( GAME_OBJECT_STATE::ACTIVE )
{
    m_ChildObjectList.clear( );
}

/*
 *  コンストラクタ
 */
aqua::IGameObject::
IGameObject( IGameObject* parent, const std::string& name, const std::string& category )
    : m_ParentObject( parent )
    , m_GameObjectName( name )
    , m_GameObjectCategory( category )
    , m_GameObjectState( GAME_OBJECT_STATE::ACTIVE )
{
    m_ChildObjectList.clear( );
}

/*
 *  初期化
 */
void
aqua::IGameObject::
Initialize( void )
{
    // リストが空なら終了
    if( m_ChildObjectList.empty( ) ) return;

    for( auto it : m_ChildObjectList )
        it->Initialize( );
}

/*
 *  更新
 */
void
aqua::IGameObject::
Update( void )
{
    // リストが空なら終了
    if( m_ChildObjectList.empty( ) ) return;

    GAME_OBJECT_LIST::iterator it  = m_ChildObjectList.begin( );
    GAME_OBJECT_LIST::iterator end = m_ChildObjectList.end( );

    while( it != end )
    {
        IGameObject* t = (*it);

        // ゲームオブジェクトの状態を取得
        GAME_OBJECT_STATE state = t->GetGameObjectState( );

        // ゲームオブジェクトの状態がデッドならリストから除外
        if( state == GAME_OBJECT_STATE::DEAD )
        {
            // 子オブジェクトをすべて解放
            t->Finalize( );

            // メモリ解放
            AQUA_SAFE_DELETE( t );

            // リストから削除
            it = m_ChildObjectList.erase( it );

            continue;
        }

        // ゲームオブジェクトの状態がアクティブなら更新
        if( state == GAME_OBJECT_STATE::ACTIVE )
            t->Update( );

        ++it;
    }
}

/*
 *  描画
 */
void
aqua::IGameObject::
Draw( void )
{
    // リストが空なら終了
    if( m_ChildObjectList.empty( ) ) return;

    for( auto it : m_ChildObjectList )
        it->Draw( );
}

/*
 *  解放
 */
void
aqua::IGameObject::
Finalize( void )
{
    // リストが空なら終了
    if( m_ChildObjectList.empty( ) ) return;

    GAME_OBJECT_LIST::iterator it = m_ChildObjectList.begin( );
    GAME_OBJECT_LIST::iterator end = m_ChildObjectList.end( );

    while( it != end )
    {
        (*it)->Finalize( );

        AQUA_SAFE_DELETE( (*it) );

        it = m_ChildObjectList.erase( it );
    }

    // リストのクリア
    m_ChildObjectList.clear( );
}

/*
 *  親オブジェクトの取得
 */
aqua::IGameObject*
aqua::IGameObject::
GetParent( void )
{
    return m_ParentObject;
}

/*
 *  子リストの取得
 */
aqua::GAME_OBJECT_LIST*
aqua::IGameObject::
GetChildList( void )
{
    return &m_ChildObjectList;
}

/*
 *  子オブジェクトの追加
 */
void
aqua::IGameObject::
AddChild( aqua::IGameObject* obj )
{
    if( !obj ) return;

    // 親オブジェクトの登録
    obj->m_ParentObject = this;
    
    // 子リストに追加
    m_ChildObjectList.push_back( obj );
}

/*
 *  子オブジェクトを先頭に追加
 */
void
aqua::IGameObject::
AddFrontChild( aqua::IGameObject* obj )
{
    if( !obj ) return;

    // 親オブジェクトの登録
    obj->m_ParentObject = this;
    
    // 子リストに追加
    m_ChildObjectList.push_front( obj );
}

/*
 *  子オブジェクトの削除
 */
aqua::IGameObject*
aqua::IGameObject::
RemoveChild( const std::string& name )
{
    // リストが空なら終了
    if( m_ChildObjectList.empty( ) ) return nullptr;

    GAME_OBJECT_LIST::iterator it  = m_ChildObjectList.begin( );
    GAME_OBJECT_LIST::iterator end = m_ChildObjectList.end( );

    while( it != end )
    {
        if( (*it)->m_GameObjectName == name )
        {
            IGameObject* t = *it;

            // リストから削除
            m_ChildObjectList.erase( it );

            return t;
        }

        ++it;
    }

    return nullptr;
}

/*
 *  子オブジェクトの削除
 */
aqua::IGameObject*
aqua::IGameObject::
RemoveChild( aqua::FIND_METHOD func )
{
    // リストが空なら終了
    if( m_ChildObjectList.empty( ) ) return nullptr;

    GAME_OBJECT_LIST::iterator it  = m_ChildObjectList.begin( );
    GAME_OBJECT_LIST::iterator end = m_ChildObjectList.end( );

    while( it != end )
    {
        if( func( *it ) )
        {
            IGameObject* t = *it;

            // リストから削除
            m_ChildObjectList.erase( it );

            return t;
        }

        ++it;
    }

    return nullptr;
}

/*
 *  子オブジェクトの検索
 */
aqua::IGameObject*
aqua::IGameObject::
FindChild( const std::string& name )
{
    // ゲームオブジェクト名が同じなら、そのオブジェクトを返す
    if( m_GameObjectName == name ) return this;

    // リストが空なら終了
    if( m_ChildObjectList.empty( ) ) return nullptr;

    for( auto& it : m_ChildObjectList )
    {
        // ゲームオブジェクトIDによって子オブジェクトを検索する
        IGameObject* t = it->FindChild( name );

        // アドレスがあれば見つかった
        if( t ) return t;
    }

    return nullptr;
}

/*
 *  子オブジェクトの検索
 */
aqua::IGameObject*
aqua::IGameObject::
FindChild( aqua::FIND_METHOD func )
{
    // 検索条件が真なら、そのオブジェクトを返す
    if( func( this ) ) return this;

    // リストが空なら終了
    if( m_ChildObjectList.empty( ) ) return nullptr;

    for( auto& it : m_ChildObjectList )
    {
        // 検索条件を与えて子オブジェクトを検索する
        IGameObject* t = it->FindChild( func );

        // アドレスがあれば見つかった
        if( t ) return t;
    }

    return nullptr;
}

/*
 *  兄弟オブジェクトの検索
 */
aqua::IGameObject*
aqua::IGameObject::
FindSibling( const std::string& name )
{
    // 親オブジェクトがいない
    if( !m_ParentObject ) return nullptr;

    // 親のリストから兄弟を検索
    return m_ParentObject->FindChild( name );
}

/*
 *  兄弟オブジェクトの検索
 */
aqua::IGameObject*
aqua::IGameObject::
FindSibling( aqua::FIND_METHOD func )
{
    // 親オブジェクトがいない
    if( !m_ParentObject ) return nullptr;

    // 親のリストから兄弟を検索
    return m_ParentObject->FindChild( func );
}

/*
 *  ゲームオブジェクトの削除
 */
void
aqua::IGameObject::
DeleteObject( void )
{
    m_GameObjectState = GAME_OBJECT_STATE::DEAD;
}

/*
 *  ゲームオブジェクト名取得
 */
std::string
aqua::IGameObject::
GetGameObjectName( void ) const
{
    return m_GameObjectName;
}

/*
 *  ゲームオブジェクトカテゴリー取得
 */
std::string
aqua::IGameObject::
GetGameObjectCategory( void ) const
{
    return m_GameObjectCategory;
}

/*
 *  ゲームオブジェクト状態取得
 */
aqua::GAME_OBJECT_STATE
aqua::IGameObject::
GetGameObjectState( void ) const
{
    return m_GameObjectState;
}

/*
 *  ゲームオブジェクト状態設定
 */
void
aqua::IGameObject::
SetGameObjectState( aqua::GAME_OBJECT_STATE state )
{
    m_GameObjectState = state;
}
