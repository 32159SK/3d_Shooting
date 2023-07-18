/*
 *  @file       scene.h
 *  @brief      �V�[��
 *  @author
 *  @date
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "scene_id.h"

 /*
  *  @class      IScene
  *
  *  @brief      �V�[���N���X
  *
  *  @author     Kazuto Shimazaki
  *
  *  @date       2023/04/20
  *
  *  @version    1.0
  */
class IScene
    : public aqua::IGameObject
{
public:
    /*
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent          �e�I�u�W�F�N�g
     *  @param[in]  object_name     �I�u�W�F�N�g��
     */
    IScene(aqua::IGameObject* parent, const std::string& object_name);

    /*
     *  @brief      �f�X�g���N�^
     */
    virtual ~IScene(void) = default;

    /*
     *  @brief      �V�[����ύX����
     *              �X�^�b�N����Ă���S�ẴV�[�����폜���ύX����
     *
     *  @param[in]  id      �V�[��ID
     */
    void    Change(SCENE_ID id);

    /*
     *  @brief      �V�[�����X�^�b�N����
     *
     *  @param[in]  id      �V�[��ID
     */
    void    Push(SCENE_ID id);

    /*
     *  @brief      �X�^�b�N���ꂽ�V�[�������o��
     */
    void    Pop(void);

    /*
     *  @brief      �V�[�������Z�b�g����
     */
    void    Reset(void);

private:
    static const std::string    m_scene_category;  //! �V�[���J�e�S���[
};

