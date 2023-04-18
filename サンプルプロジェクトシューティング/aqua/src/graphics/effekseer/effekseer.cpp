
/*!
 *  @file       effekseer.cpp
 *  @brief      Effekseerクラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include <windows.h>
#include "effekseer.h"
#include "effekseer_manager\effekseer_manager.h"

/*
 *  コンストラクタ
 */
aqua::CEffekseer::
CEffekseer( void )
    : m_EffekseerResource( nullptr )
{
}

/*
 *  コピーコンストラクタ
 */
aqua::CEffekseer::
CEffekseer( const aqua::CEffekseer& effect )
    : m_EffekseerResource( nullptr )
{
    if( m_EffekseerResource )
        m_EffekseerResource->RemoveReference( );

    m_EffekseerResource = effect.m_EffekseerResource;

    // 参照カウンタ加算
    m_EffekseerResource->AddReference( );
}

/*
 *  Effekseer読み込み
 */
void
aqua::CEffekseer::
Load( const std::string& file_name )
{
    // Effekseerリソース退避
    core::CEffekseerResource* effect = m_EffekseerResource;

    // EffekseerマネージャからEffekseer取得
    m_EffekseerResource = core::CEffekseerManager::GetInstance( ).Load( file_name );

    if( effect )
    {
        int count = effect->RemoveReference( );

        // 前のEffekseerの参照カウンタがなくなったら解放
        if( count <= 0 )
            core::CEffekseerManager::GetInstance( ).Unload( effect );
    }
}

/*
 *  Effekseer解放
 */
void
aqua::CEffekseer::
Unload( void )
{
    // Effekseer解放
    if( m_EffekseerResource )
        core::CEffekseerManager::GetInstance( ).Unload( m_EffekseerResource );

    m_EffekseerResource = nullptr;
}

/*
 *  代入演算子のオーバーロード
 */
aqua::CEffekseer&
aqua::CEffekseer::
operator=( const aqua::CEffekseer& effect )
{
    // Effekseerを持っていたら参照を減算
    if( m_EffekseerResource )
        m_EffekseerResource->RemoveReference( );

    m_EffekseerResource = effect.m_EffekseerResource;

    // 参照カウンタ加算
    m_EffekseerResource->AddReference( );

    return *this;
}
