#pragma once

enum class BULLET_TYPE
{
	NOMAL,
	MAX
};

struct BULLET_INFO
{
    int     damage = 1;
    float   radius = 5;
    float   speed = 2.0f;
    aqua::CColor color = aqua::CColor::RED;
};
