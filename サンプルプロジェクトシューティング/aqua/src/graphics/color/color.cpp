
/*!
 *  @file       color.cpp
 *  @brief      色
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "color.h"
#include "..\..\debug\debug.h"
#include <cmath>

#define COLORToALPHA( color )   (unsigned char)( ( ( color ) & 0xff000000 ) >> 24 )
#define COLORToRED( color )     (unsigned char)( ( ( color ) & 0x00ff0000 ) >> 16 )
#define COLORToGREEN( color )   (unsigned char)( ( ( color ) & 0x0000ff00 ) >>  8 )
#define COLORToBLUE( color )    (unsigned char)( ( ( color ) & 0x000000ff ) >>  0 )

const unsigned char aqua::CColor::MAX_COLOR     = 0xff;
const aqua::CColor  aqua::CColor::WHITE         = 0xffffffff;
const aqua::CColor  aqua::CColor::BLACK         = 0xff000000;
const aqua::CColor  aqua::CColor::RED           = 0xffff0000;
const aqua::CColor  aqua::CColor::GREEN         = 0xff00ff00;
const aqua::CColor  aqua::CColor::BLUE          = 0xff0000ff;
const aqua::CColor  aqua::CColor::CYAN          = 0xff00ffff;
const aqua::CColor  aqua::CColor::MAGENTA       = 0xffff00ff;
const aqua::CColor  aqua::CColor::YELLOW        = 0xffffff00;

/*
 *  コンストラクタ
 */
aqua::CColor::
CColor( void )
    : alpha( MAX_COLOR )
    , red( MAX_COLOR )
    , green( MAX_COLOR )
    , blue( MAX_COLOR )
{
}

/*
 *  コンストラクタ
 */
aqua::CColor::
CColor( unsigned int color )
    : alpha( COLORToALPHA( color ) )
    , red( COLORToRED( color ) )
    , green( COLORToGREEN( color ) )
    , blue( COLORToBLUE( color ) )
{
}

/*
 *  コンストラクタ
 */
aqua::CColor::
CColor( unsigned char a, unsigned char r, unsigned char g, unsigned char b )
    : alpha( a )
    , red( r )
    , green( g )
    , blue( b )
{
}

/*
 *  代入演算子
 */
aqua::CColor&
aqua::CColor::
operator=( unsigned int color )
{

    alpha = COLORToALPHA( color );
    red   = COLORToRED( color );
    green = COLORToGREEN( color );
    blue  = COLORToBLUE( color );

    return *this;
}

/*
 *  代入演算子
 */
aqua::CColor&
aqua::CColor::
operator=( const CColor& color )
{
    alpha = color.alpha;
    red   = color.red;
    green = color.green;
    blue  = color.blue;

    return *this;
}

/*
 *  色の取得
 */
unsigned int
aqua::CColor::
GetColor( void ) const
{
    return ( ( alpha << 24 ) | ( red << 16 ) | ( green << 8 ) | blue );
}


/*
 *  色相環
 */
unsigned int
aqua::CColor::
ChangeHSVToColor(float hue, float saturation, float brightness)
{
    int r = 0, g = 0, b = 0;
    int region = 0;
    float fraction = 0.0f;
    int min = 0, max = 0, up = 0, down = 0;

    while (hue > 360.0f || hue < 0.0f)
    {
        if (hue >= 360.0f)     hue -= 360.0f;
        else if (hue < 0.0f)   hue += 360.0f;
    }

    if (saturation > 1.0f) saturation = 1.0f;
    else if (saturation < 0.0f) saturation = 0.0f;

    if (brightness > 1.0f) brightness = 1.0f;
    else if (brightness < 0.0f) brightness = 0.0f;

    max = (int)(brightness * 255);

    if (saturation == 0.0f)
    {
        r = max;
        g = max;
        b = max;
    }
    else
    {
        region = (int)(hue / 60.0f);
        fraction = hue / 60.0f - region;
        min = (int)(max * (1.0f - saturation));
        up = min + (int)(fraction * max * saturation);
        down = max - (int)(fraction * max * saturation);

        switch (region)
        {
        case 0:r = max;  g = up;  b = min; break;
        case 1:r = down;  g = max; b = min; break;
        case 2:r = min;  g = max; b = up;  break;
        case 3:r = min;  g = down; b = max; break;
        case 4:r = up;   g = min; b = max; break;
        case 5:r = max;  g = min; b = down; break;
        }
    }

    return (0xff << 24 | (unsigned char)r << 16 | (unsigned char)g << 8 | (unsigned char)b);
}

/*
 *  色相環から色を取得
 */
unsigned int
aqua::CColor::
ChangeNumberToColor(int step, int number)
{
    number %= step;

    float hue = 360.0f / (float)step * (float)number;

    return ChangeHSVToColor(hue, 1.0f, 1.0f);
}

/*
 *  デバッグログに出力する
 */
void
aqua::CColor::
DebugLog( void )
{
    AQUA_DEBUG_LOG( "CColor(A:" + std::to_string( alpha ) + ", R:" + std::to_string( red ) + ", G:" + std::to_string( green ) + ", B:" + std::to_string( blue ) + ")" );
}
