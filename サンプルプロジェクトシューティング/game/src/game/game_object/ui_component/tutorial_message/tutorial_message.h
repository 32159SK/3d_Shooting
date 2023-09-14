
#pragma once

#include "..\ui_component.h"

/*!
 *  @class      CTutorialMessage
 *
 *  @brief      �`���[�g���A�����b�Z�[�W�`��N���X
 *
 *  @author     Kazuto Shimazaki
 *
 *  @date
 *
 *  @version    1.0
 */
class CTutorialMessage
    : public IUIComponent
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�̃I�u�W�F�N�g
     */
    CTutorialMessage(aqua::IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CTutorialMessage(void) = default;

    /*!
     *  @brief      ������
     */
    void        Initialize(std::string text);

    /*!
     *  @brief      �X�V
     */
    void        Update(void) override;

    /*!
     *  @brief      �`��
     */
    void        Draw(void) override;

    /*!
     *  @brief      ���
     */
    void        Finalize(void) override;

private:
    /*!
     *  @brief      �o��
     */
    void        PopIn(void);

    /*!
     *  @brief      �ҋ@
     */
    void        Wait(void);

    /*!
     *  @brief      ������
     */
    void        PopOut(void);


    enum class STATE
    {
        POP_IN,     // �o��
        WAIT,       // �ҋ@
        POP_OUT,    // ������
        END         // �I��
    };

    static const float      m_pop_time;                 // �o��̂ɂ����鎞��
    static const float      m_wait_time;                // �ҋ@����
    static const float      m_background_panel_height;  // �p�l���̍���

    aqua::CTimer            m_Timer;                    // �^�C�}�[
    aqua::CBoxPrimitive     m_WindowPanel;              // �p�l��
    aqua::CLabel            m_FunctionName;             // �@�\��
    aqua::CLabel            m_Message;                  // �e�L�X�g�N���X
    STATE                   m_State;                    // ���
};
