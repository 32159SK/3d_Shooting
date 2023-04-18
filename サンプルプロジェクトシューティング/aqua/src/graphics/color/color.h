
/*!
 *  @file       color.h
 *  @brief      �F
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

/*!
 *  @brief  aqua���O���
 */
namespace aqua
{
    /*!
     *  @class      CColor
     *
     *  @brief      �F�N���X
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CColor
    {
    public:
        /*!
         *  @brief      �R���X�g���N�^
         */
        CColor( void );

        /*!
         *  @brief      �R���X�g���N�^<br>
         *              ARGB(32bit)
         *
         *  @param[in]  color   ARGB�F
         */
        CColor( unsigned int color );

        /*!
         *  @brief      �R���X�g���N�^<br>
         *              �e�l0�`255
         *
         *  @param[in]  a   �A���t�@�l
         *  @param[in]  r   ���b�h�l
         *  @param[in]  g   �O���[���l
         *  @param[in]  b   �u���[�l
         */
        CColor( unsigned char a, unsigned char r, unsigned char g, unsigned char b );

        /*!
         *  @brief      �f�X�g���N�^
         */
        ~CColor(void) = default;

        /*!
         *  @brief      ������Z�q
         *
         *  @param[in]  color   �J���[(ARGB32bit)
         *
         *  @return     �J���[�N���X
         */
        CColor&         operator=( unsigned int color );

        /*!
         *  @brief      ������Z�q
         *
         *  @param[in]  color   �J���[�N���X
         *
         *  @return     �J���[�N���X
         */
        CColor&         operator=( const CColor& color );

        /*!
         *  @brief      �F�̎擾
         *
         *  @return     ARGB(32bit)
         */
        unsigned int    GetColor( void ) const;

        /*!
         *  @brief      �f�o�b�O���O�ɒl��\������
         */
        void            DebugLog(void);

        /*!
         *  @brief      �F������F���擾
         *
         *  @param[in]  hue         �F��
         *  @param[in]  saturation  �ʓx
         *  @param[in]  brightness  ���x
         *
         *  @return     �F
         */
        static unsigned int    ChangeHSVToColor(float hue, float saturation, float brightness);

        /*!
         *  @brief      ���������ɐF������F���擾
         *
         *  @param[in]  step    �ߖڂƂȂ�l
         *  @param[in]  number  �J���[�ɕϊ����鐔�l
         *
         *  @return     �F
         */
        static unsigned int    ChangeNumberToColor(int step, int number);

        //! �J���[�̍ő�l
        static const unsigned char  MAX_COLOR;
        //! �z���C�g
        static const CColor         WHITE;
        //! �u���b�N
        static const CColor         BLACK;
        //! ���b�h
        static const CColor         RED;
        //! �O���[��
        static const CColor         GREEN;
        //! �u���[
        static const CColor         BLUE;
        //! �V�A��
        static const CColor         CYAN;
        //! �}�[���^
        static const CColor         MAGENTA;
        //! �C�G���[
        static const CColor         YELLOW;
        //! �A���t�@�l
        unsigned char               alpha;
        //! ���b�h�l
        unsigned char               red;
        //! �O���[���l
        unsigned char               green;
        //! �u���[�l
        unsigned char               blue;
    };
}
