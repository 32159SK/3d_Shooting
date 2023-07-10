#pragma once

enum class BULLET_TYPE
{
    NOMAL,
    REFLECT,
    PENETRATE,
    BEAM,
    MAX
};

struct BULLET_INFO
{
    BULLET_TYPE bullet_type = BULLET_TYPE::NOMAL;
    int     damage = 1;
    float   radius = 5.0f;
    float   speed = 2.0f;
};
