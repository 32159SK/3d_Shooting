
/*!
 *  @file       game_object.cpp
 *  @brief      �Q�[���I�u�W�F�N�g�x�[�X
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "game_object.h"

/*
 *  �R���X�g���N�^
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
 *  �R���X�g���N�^
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
 *  �R���X�g���N�^
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
 *  �R���X�g���N�^
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
 *  ������
 */
void
aqua::IGameObject::
Initialize( void )
{
    // ���X�g����Ȃ�I��
    if( m_ChildObjectList.empty( ) ) return;

    for( auto it : m_ChildObjectList )
        it->Initialize( );
}

/*
 *  �X�V
 */
void
aqua::IGameObject::
Update( void )
{
    // ���X�g����Ȃ�I��
    if( m_ChildObjectList.empty( ) ) return;

    GAME_OBJECT_LIST::iterator it  = m_ChildObjectList.begin( );
    GAME_OBJECT_LIST::iterator end = m_ChildObjectList.end( );

    while( it != end )
    {
        IGameObject* t = (*it);

        // �Q�[���I�u�W�F�N�g�̏�Ԃ��擾
        GAME_OBJECT_STATE state = t->GetGameObjectState( );

        // �Q�[���I�u�W�F�N�g�̏�Ԃ��f�b�h�Ȃ烊�X�g���珜�O
        if( state == GAME_OBJECT_STATE::DEAD )
        {
            // �q�I�u�W�F�N�g�����ׂĉ��
            t->Finalize( );

            // ���������
            AQUA_SAFE_DELETE( t );

            // ���X�g����폜
            it = m_ChildObjectList.erase( it );

            continue;
        }

        // �Q�[���I�u�W�F�N�g�̏�Ԃ��A�N�e�B�u�Ȃ�X�V
        if( state == GAME_OBJECT_STATE::ACTIVE )
            t->Update( );

        ++it;
    }
}

/*
 *  �`��
 */
void
aqua::IGameObject::
Draw( void )
{
    // ���X�g����Ȃ�I��
    if( m_ChildObjectList.empty( ) ) return;

    for( auto it : m_ChildObjectList )
        it->Draw( );
}

/*
 *  ���
 */
void
aqua::IGameObject::
Finalize( void )
{
    // ���X�g����Ȃ�I��
    if( m_ChildObjectList.empty( ) ) return;

    GAME_OBJECT_LIST::iterator it = m_ChildObjectList.begin( );
    GAME_OBJECT_LIST::iterator end = m_ChildObjectList.end( );

    while( it != end )
    {
        (*it)->Finalize( );

        AQUA_SAFE_DELETE( (*it) );

        it = m_ChildObjectList.erase( it );
    }

    // ���X�g�̃N���A
    m_ChildObjectList.clear( );
}

/*
 *  �e�I�u�W�F�N�g�̎擾
 */
aqua::IGameObject*
aqua::IGameObject::
GetParent( void )
{
    return m_ParentObject;
}

/*
 *  �q���X�g�̎擾
 */
aqua::GAME_OBJECT_LIST*
aqua::IGameObject::
GetChildList( void )
{
    return &m_ChildObjectList;
}

/*
 *  �q�I�u�W�F�N�g�̒ǉ�
 */
void
aqua::IGameObject::
AddChild( aqua::IGameObject* obj )
{
    if( !obj ) return;

    // �e�I�u�W�F�N�g�̓o�^
    obj->m_ParentObject = this;
    
    // �q���X�g�ɒǉ�
    m_ChildObjectList.push_back( obj );
}

/*
 *  �q�I�u�W�F�N�g��擪�ɒǉ�
 */
void
aqua::IGameObject::
AddFrontChild( aqua::IGameObject* obj )
{
    if( !obj ) return;

    // �e�I�u�W�F�N�g�̓o�^
    obj->m_ParentObject = this;
    
    // �q���X�g�ɒǉ�
    m_ChildObjectList.push_front( obj );
}

/*
 *  �q�I�u�W�F�N�g�̍폜
 */
aqua::IGameObject*
aqua::IGameObject::
RemoveChild( const std::string& name )
{
    // ���X�g����Ȃ�I��
    if( m_ChildObjectList.empty( ) ) return nullptr;

    GAME_OBJECT_LIST::iterator it  = m_ChildObjectList.begin( );
    GAME_OBJECT_LIST::iterator end = m_ChildObjectList.end( );

    while( it != end )
    {
        if( (*it)->m_GameObjectName == name )
        {
            IGameObject* t = *it;

            // ���X�g����폜
            m_ChildObjectList.erase( it );

            return t;
        }

        ++it;
    }

    return nullptr;
}

/*
 *  �q�I�u�W�F�N�g�̍폜
 */
aqua::IGameObject*
aqua::IGameObject::
RemoveChild( aqua::FIND_METHOD func )
{
    // ���X�g����Ȃ�I��
    if( m_ChildObjectList.empty( ) ) return nullptr;

    GAME_OBJECT_LIST::iterator it  = m_ChildObjectList.begin( );
    GAME_OBJECT_LIST::iterator end = m_ChildObjectList.end( );

    while( it != end )
    {
        if( func( *it ) )
        {
            IGameObject* t = *it;

            // ���X�g����폜
            m_ChildObjectList.erase( it );

            return t;
        }

        ++it;
    }

    return nullptr;
}

/*
 *  �q�I�u�W�F�N�g�̌���
 */
aqua::IGameObject*
aqua::IGameObject::
FindChild( const std::string& name )
{
    // �Q�[���I�u�W�F�N�g���������Ȃ�A���̃I�u�W�F�N�g��Ԃ�
    if( m_GameObjectName == name ) return this;

    // ���X�g����Ȃ�I��
    if( m_ChildObjectList.empty( ) ) return nullptr;

    for( auto& it : m_ChildObjectList )
    {
        // �Q�[���I�u�W�F�N�gID�ɂ���Ďq�I�u�W�F�N�g����������
        IGameObject* t = it->FindChild( name );

        // �A�h���X������Ό�������
        if( t ) return t;
    }

    return nullptr;
}

/*
 *  �q�I�u�W�F�N�g�̌���
 */
aqua::IGameObject*
aqua::IGameObject::
FindChild( aqua::FIND_METHOD func )
{
    // �����������^�Ȃ�A���̃I�u�W�F�N�g��Ԃ�
    if( func( this ) ) return this;

    // ���X�g����Ȃ�I��
    if( m_ChildObjectList.empty( ) ) return nullptr;

    for( auto& it : m_ChildObjectList )
    {
        // ����������^���Ďq�I�u�W�F�N�g����������
        IGameObject* t = it->FindChild( func );

        // �A�h���X������Ό�������
        if( t ) return t;
    }

    return nullptr;
}

/*
 *  �Z��I�u�W�F�N�g�̌���
 */
aqua::IGameObject*
aqua::IGameObject::
FindSibling( const std::string& name )
{
    // �e�I�u�W�F�N�g�����Ȃ�
    if( !m_ParentObject ) return nullptr;

    // �e�̃��X�g����Z�������
    return m_ParentObject->FindChild( name );
}

/*
 *  �Z��I�u�W�F�N�g�̌���
 */
aqua::IGameObject*
aqua::IGameObject::
FindSibling( aqua::FIND_METHOD func )
{
    // �e�I�u�W�F�N�g�����Ȃ�
    if( !m_ParentObject ) return nullptr;

    // �e�̃��X�g����Z�������
    return m_ParentObject->FindChild( func );
}

/*
 *  �Q�[���I�u�W�F�N�g�̍폜
 */
void
aqua::IGameObject::
DeleteObject( void )
{
    m_GameObjectState = GAME_OBJECT_STATE::DEAD;
}

/*
 *  �Q�[���I�u�W�F�N�g���擾
 */
std::string
aqua::IGameObject::
GetGameObjectName( void ) const
{
    return m_GameObjectName;
}

/*
 *  �Q�[���I�u�W�F�N�g�J�e�S���[�擾
 */
std::string
aqua::IGameObject::
GetGameObjectCategory( void ) const
{
    return m_GameObjectCategory;
}

/*
 *  �Q�[���I�u�W�F�N�g��Ԏ擾
 */
aqua::GAME_OBJECT_STATE
aqua::IGameObject::
GetGameObjectState( void ) const
{
    return m_GameObjectState;
}

/*
 *  �Q�[���I�u�W�F�N�g��Ԑݒ�
 */
void
aqua::IGameObject::
SetGameObjectState( aqua::GAME_OBJECT_STATE state )
{
    m_GameObjectState = state;
}
