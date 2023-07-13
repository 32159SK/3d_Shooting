#pragma once


/*!
 *  @brief      �e��
 */
enum class BULLET_TYPE
{
    NORMAL,     // �ʏ�e
    REFLECT,    // ���˒e
    PENETRATE,  // �n�`�ђʒe
    BEAM,       // �Qt...�r�[��
    MAX
};


/*!
 *  @brief      �e���
 */
struct BULLET_INFO
{
    BULLET_TYPE bullet_type = BULLET_TYPE::NORMAL;  // �e��
    int     damage = 1;                             // �_���[�W�l
    float   radius = 5.0f;                          // ���a
    float   speed = 1.0f;                           // �e��
};
