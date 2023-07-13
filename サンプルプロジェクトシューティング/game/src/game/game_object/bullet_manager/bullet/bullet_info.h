#pragma once

enum class BULLET_TYPE
{
    NORMAL,
    REFLECT,
    PENETRATE,
    BEAM,
    MAX
};

struct BULLET_INFO
{
    BULLET_TYPE bullet_type = BULLET_TYPE::NORMAL;
    int     damage = 1;
    float   radius = 5.0f;
    float   speed = 1.0f;
};
