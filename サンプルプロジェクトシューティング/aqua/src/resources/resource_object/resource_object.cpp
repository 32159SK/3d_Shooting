
/*!
 *  @file       resource_object.cpp
 *  @brief      リソースオブジェクト用インターフェース
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013, Kazuya Maruyama. All rights reserved.
 */

#include "resource_object.h"

/*
 *  コンストラクタ
 */
aqua::core::IResourceObject::
IResourceObject( void )
    : m_ResourceType( RESOURCE_TYPE::DUMMY )
    , m_ResourceName( "none" )
    , m_ResourceHandle( AQUA_UNUSED_HANDLE )
    , m_ReferenceCount( 0 )
    , m_Enabel( false )
{
}

/*
 *  コンストラクタ
 */
aqua::core::IResourceObject::
IResourceObject( aqua::core::RESOURCE_TYPE type )
    : m_ResourceType( type )
    , m_ResourceName( "none" )
    , m_ResourceHandle( AQUA_UNUSED_HANDLE )
    , m_ReferenceCount( 0 )
    , m_Enabel( false )
{
}

/*
 *  コンストラクタ
 */
aqua::core::IResourceObject::
    IResourceObject( aqua::core::RESOURCE_TYPE type, const std::string& name )
    : m_ResourceType( type )
    , m_ResourceName( name )
    , m_ResourceHandle( AQUA_UNUSED_HANDLE )
    , m_ReferenceCount( 0 )
    , m_Enabel( false )
{
}
