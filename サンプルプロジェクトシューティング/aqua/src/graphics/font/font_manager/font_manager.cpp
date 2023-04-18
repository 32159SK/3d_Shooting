
/*!
 *  @file       font_manager.cpp
 *  @brief      �t�H���g�Ǘ��N���X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "font_manager.h"
#include "..\..\..\debug\debug.h"
#include "..\..\..\utility\memory\memory.h"

/*
 *  �C���X�^���X�̎擾
 */
aqua::core::CFontManager&
aqua::core::CFontManager::
GetInstance( void )
{
    static CFontManager instance;

    return instance;
}

/*
 *  �t�H���g����
 */
aqua::core::CFontResource*
aqua::core::CFontManager::
Create( int size, int edge_bold, bool anti_aliasing, aqua::FONT_FAMILY_ID family_id )
{
    // �t�H���g����
    CFontResource* font = Find( size, edge_bold, family_id );

    // �t�H���g��������Ȃ�����
    if( !font )
    {
        // �V�����t�H���g����
        font = AQUA_NEW CFontResource( );

        // �ǂݍ���
        font->Create( size, edge_bold, anti_aliasing, family_id );

        // �t�H���g���X�g�ɒǉ�
        m_FontList.push_back( font );
    }

    // �Q�ƃJ�E���^���Z
    font->AddReference( );

    return font;
}

/*
 *  �t�H���g���
 */
void
aqua::core::CFontManager::
Delete( aqua::core::CFontResource* font )
{
    if( !font ) return;

    if( m_FontList.empty( ) ) return;

    // �Q�ƃJ�E���^���Z
    // �Q�Ƃ��Ȃ��Ȃ�������
    if( font->RemoveReference( ) > 0 ) return;

    FONT_LIST::iterator it  = m_FontList.begin( );
    FONT_LIST::iterator end = m_FontList.end( );

    while( it != end )
    {
        if( (*it)->CheckFont( font ) )
        {
            (*it)->Delete( );

            AQUA_SAFE_DELETE( (*it) );

            m_FontList.erase( it );

            break;
        }

        ++it;
    }
}

/*
 *  �t�H���g�N���X�̌���
 */
aqua::core::CFontResource*
aqua::core::CFontManager::
Find( int size, int edge_bold, aqua::FONT_FAMILY_ID family_id )
{
    if( m_FontList.empty( ) ) return nullptr;

    FONT_LIST::iterator it  = m_FontList.begin( );
    FONT_LIST::iterator end = m_FontList.end( );

    // ��v�����t�H���g�N���X��Ԃ�
    while( it != end )
    {
        if( ( *it )->CheckFont( size, edge_bold, family_id ) )
            return ( *it );

        ++it;
    }

    return nullptr;
}

/*
 *  �t�H���g���X�g�̃N���A
 */
void
aqua::core::CFontManager::
Clear( void )
{
    if( m_FontList.empty( ) ) return;

    FONT_LIST::iterator it  = m_FontList.begin( );
    FONT_LIST::iterator end = m_FontList.end( );

    while( it != end )
    {
        if( (*it) )
        {
            // �t�H���g���
            (*it)->Delete( );

            AQUA_SAFE_DELETE( (*it) );
        }

        ++it;
    }

    // �t�H���g���X�g���
    m_FontList.clear( );
}

/*
 *  �R���X�g���N�^
 */
aqua::core::CFontManager::
CFontManager( void )
{
    m_FontList.clear( );
}

/*
 *  �R�s�[�R���X�g���N�^
 */
aqua::core::CFontManager::
CFontManager( const aqua::core::CFontManager& rhs )
{
    (void)rhs;
}

/*
 *  ������Z�q
 */
aqua::core::CFontManager&
aqua::core::CFontManager::
operator=( const aqua::core::CFontManager& rhs )
{
    (void)rhs;

    return *this;
}
