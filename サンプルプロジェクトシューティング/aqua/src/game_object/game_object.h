
/*!
 *  @file       game_object.h
 *  @brief      �Q�[���I�u�W�F�N�g�x�[�X
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
 *  @brief      aqua���O���
 */
namespace aqua
{
    /*!
     *  @brief      �I�u�W�F�N�g�N���X�̑O���錾
     */
    class IGameObject;

    /*!
     *  @brief      �I�u�W�F�N�g�N���X���X�g�^
     */
    typedef std::list<IGameObject*> GAME_OBJECT_LIST;

    /*!
     *  @brief      �����֐��o�^�p�֐��|�C���^
     */
    typedef bool (*FIND_METHOD)( IGameObject* arg );

    /*!
     *  @brief      �Q�[���I�u�W�F�N�g���ID
     */
    enum class GAME_OBJECT_STATE
    {
        //! �ҋ@(�X�V�Ȃ��A�`��̂�)
        WAIT,
        //! �X�V�E�`��
        ACTIVE,
        //! ���S(�q�I�u�W�F�N�g�����ׂĉ��)
        DEAD,
    };

    /*!
     *  @class      IGameObject
     *
     *  @brief      �Q�[���I�u�W�F�N�g�x�[�X�N���X
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
         *  @brief      �R���X�g���N�^
         */
        IGameObject( void );

        /*!
         *  @brief      �R���X�g���N�^
         *
         *  @param[in]  parent  �e�̃I�u�W�F�N�g
         */
        IGameObject( IGameObject* parent );

        /*!
         *  @brief      �R���X�g���N�^
         *
         *  @param[in]  parent  �e�̃I�u�W�F�N�g
         *  @param[in]  name    �I�u�W�F�N�g��
         */
        IGameObject( IGameObject* parent, const std::string& name );

        /*!
         *  @brief      �R���X�g���N�^
         *
         *  @param[in]  parent      �e�̃I�u�W�F�N�g
         *  @param[in]  name        �I�u�W�F�N�g��
         *  @param[in]  category    �J�e�S���[
         */
        IGameObject( IGameObject* parent, const std::string& name, const std::string& category );

        /*!
         *  @brief      �f�X�g���N�^
         */
        virtual ~IGameObject( void ) = default;

        /*!
         *  @brief      ������
         */
        virtual void        Initialize( void );

        /*!
         *  @brief      �X�V
         */
        virtual void        Update( void );

        /*!
         *  @brief      �`��
         */
        virtual void        Draw( void );

        /*!
         *  @brief      ���
         */
        virtual void        Finalize( void );

        /*!
         *  @brief      �e�I�u�W�F�N�g�̎擾
         *
         *  @return     �e�̃I�u�W�F�N�g<br>
         *              ���[�g�̏ꍇ��nullptr
         */
        IGameObject*        GetParent( void );

        /*!
         *  @brief      �q�I�u�W�F�N�g���X�g�̎擾
         *
         *  @return     �q�I�u�W�F�N�g���X�g
         */
        GAME_OBJECT_LIST*   GetChildList( void );

        /*!
         *  @brief      �q�I�u�W�F�N�g�̒ǉ�
         *
         *  @param[in]  obj     �q�̃I�u�W�F�N�g
         */
        void                AddChild( IGameObject* obj );

        /*!
         *  @brief      �q�I�u�W�F�N�g��擪�ɒǉ�
         *
         *  @param[in]  obj     �q�̃I�u�W�F�N�g
         */
        void                AddFrontChild( IGameObject* obj );

        /*!
         *  @brief      �q�I�u�W�F�N�g�̍폜
         *
         *  @param[in]  name    �I�u�W�F�N�g�̖��O
         *
         *  @return     ���X�g����폜�����q�̃I�u�W�F�N�g<br>
         *              ������Ȃ������ꍇ��nullptr
         */
        IGameObject*        RemoveChild( const std::string& name );

        /*!
         *  @brief      �q�I�u�W�F�N�g�̍폜
         *
         *  @param[in]  func    �폜�������\�b�h
         *
         *  @return     ���X�g����폜�����q�̃I�u�W�F�N�g<br>
         *              ������Ȃ������ꍇ��nullptr
         */
        IGameObject*        RemoveChild( FIND_METHOD func );

        /*!
         *  @brief      �q�̃I�u�W�F�N�g����
         *
         *  @param[in]  name    �I�u�W�F�N�g�̖��O
         *
         *  @return     �����I�u�W�F�N�g<br>
         *              ������Ȃ������ꍇ��nullptr
         */
        IGameObject*        FindChild( const std::string& name );

        /*!
         *  @brief      �q�̃I�u�W�F�N�g����
         *
         *  @param[in]  func    �����������\�b�h
         *
         *  @return     �����I�u�W�F�N�g<br>
         *              ������Ȃ������ꍇ��nullptr
         */
        IGameObject*        FindChild( FIND_METHOD func );

        /*!
         *  @brief      �Z��I�u�W�F�N�g����
         *
         *  @param[in]  name    �I�u�W�F�N�g�̖��O
         *
         *  @return     �����I�u�W�F�N�g<br>
         *              ������Ȃ������ꍇ��nullptr
         */
        IGameObject*        FindSibling( const std::string& name );

        /*!
         *  @brief      �Z��I�u�W�F�N�g����
         *
         *  @param[in]  func    �����������\�b�h
         *
         *  @return     �����I�u�W�F�N�g<br>
         *              ������Ȃ������ꍇ��nullptr
         */
        IGameObject*        FindSibling( FIND_METHOD func );

        /*!
         *  @brief      �Q�[���I�u�W�F�N�g�̍폜
         */
        void                DeleteObject( void );

        /*!
         *  @brief      �Q�[���I�u�W�F�N�gID�擾
         *
         *  @return     �Q�[���I�u�W�F�N�gID
         */
        std::string         GetGameObjectName( void ) const;

        /*!
         *  @brief      �Q�[���I�u�W�F�N�g�J�e�S���[�擾
         *
         *  @return     �Q�[���I�u�W�F�N�g�J�e�S���[
         */
        std::string         GetGameObjectCategory( void ) const;

        /*!
         *  @brief      �Q�[���I�u�W�F�N�g��Ԏ擾
         *
         *  @return     �Q�[���I�u�W�F�N�g���
         */
        GAME_OBJECT_STATE   GetGameObjectState( void ) const;

        /*!
         *  @brief      �Q�[���I�u�W�F�N�g��Ԑݒ�
         *
         *  @param[in]  state   �Q�[���I�u�W�F�N�g���
         */
        void                SetGameObjectState( GAME_OBJECT_STATE state );

    protected:
        //! �e�̃I�u�W�F�N�g
        IGameObject*                m_ParentObject;
        //! �Q�[���I�u�W�F�N�g���X�g
        GAME_OBJECT_LIST            m_ChildObjectList;
        //! �Q�[���I�u�W�F�N�g��
        std::string                 m_GameObjectName;
        //! �Q�[���I�u�W�F�N�g�̃J�e�S���[
        std::string                 m_GameObjectCategory;
        //! �Q�[���I�u�W�F�N�g���
        GAME_OBJECT_STATE           m_GameObjectState;
    };

    /*!
     *  @brief      �Q�[���I�u�W�F�N�g����
     *
     *  @param[in]  parent  �e�I�u�W�F�N�g
     *
     *  @return     �������ꂽ�Q�[���I�u�W�F�N�g
     */
    template <class T>
    T*  CreateGameObject(IGameObject* parent)
    {
        // �Q�[���I�u�W�F�N�g����
        T* t = AQUA_NEW T(parent);

        // �e������΃��X�g�ɒǉ�
        if (parent) parent->AddChild(t);

        // �I�u�W�F�N�g�̕ԋp
        return t;
    }

    /*!
     *  @brief      �Q�[���I�u�W�F�N�g����
     *
     *  @param[in]  parent  �e�I�u�W�F�N�g
     *  @param[in]  name    �I�u�W�F�N�g��
     *
     *  @return     �������ꂽ�Q�[���I�u�W�F�N�g
     */
    template <class T>
    T*  CreateGameObject(IGameObject* parent, const std::string& name)
    {
        // �Q�[���I�u�W�F�N�g����
        T* t = AQUA_NEW T(parent, name);

        // �e������΃��X�g�ɒǉ�
        if (parent) parent->AddChild(t);

        // �I�u�W�F�N�g�̕ԋp
        return t;
    }

    /*!
     *  @brief      �Q�[���I�u�W�F�N�g����<br>
     *              �q���X�g�̐擪�ɒǉ�����
     *
     *  @param[in]  parent  �e�I�u�W�F�N�g
     *
     *  @return     �������ꂽ�Q�[���I�u�W�F�N�g
     */
    template <class T>
    T*  CreateGameObjectF(IGameObject* parent)
    {
        // �Q�[���I�u�W�F�N�g����
        T* t = AQUA_NEW T(parent);

        // �e������΃��X�g�ɒǉ�
        if (parent) parent->AddFrontChild(t);

        // �I�u�W�F�N�g�̕ԋp
        return t;
    }

    /*!
     *  @brief      �Q�[���I�u�W�F�N�g����<br>
     *              �q���X�g�̐擪�ɒǉ�����
     *
     *  @param[in]  parent  �e�I�u�W�F�N�g
     *  @param[in]  name    �I�u�W�F�N�g��
     *
     *  @return     �������ꂽ�Q�[���I�u�W�F�N�g
     */
    template <class T>
    T*  CreateGameObjectF(IGameObject* parent, const std::string& name)
    {
        // �Q�[���I�u�W�F�N�g����
        T* t = AQUA_NEW T(parent, name);

        // �e������΃��X�g�ɒǉ�
        if (parent) parent->AddFrontChild(t);

        // �I�u�W�F�N�g�̕ԋp
        return t;
    }
}
