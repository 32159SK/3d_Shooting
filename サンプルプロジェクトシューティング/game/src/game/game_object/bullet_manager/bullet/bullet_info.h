#pragma once


/*!
 *  @brief      íeéÌ
 */
enum class BULLET_TYPE
{
    NORMAL,     // í èÌíe
    REFLECT,    // îΩéÀíe
    PENETRATE,  // ínå`ä—í íe
    BEAM,       // ÉQt...ÉrÅ[ÉÄ
    MAX
};


/*!
 *  @brief      íeèÓïÒ
 */
struct BULLET_INFO
{
    BULLET_TYPE bullet_type = BULLET_TYPE::NORMAL;  // íeéÌ
    int     damage = 1;                             // É_ÉÅÅ[ÉWíl
    float   radius = 5.0f;                          // îºåa
    float   speed = 1.0f;                           // íeë¨
};
