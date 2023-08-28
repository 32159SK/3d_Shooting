
/*!
 *  @file       line_primitive_3d.cpp
 *  @brief      3D線分描画クラス
 *  @author     Toshihito Ohashi
 *  @date       2022/03/29
 *  @version    7.17
 *
 *  Copyright (c) 2021-2022, Toshihto Ohahsi. All rights reserved.
 */

#include "3d_cube_primitive.h"
#include "..\..\..\debug\debug.h"

const int aqua::CCubePrimitive::polygon_count = 12;
const int aqua::CCubePrimitive::vertex_count = 8;
const int aqua::CCubePrimitive::index_count = 36;
 /*
  *  コンストラクタ
  */
aqua::CCubePrimitive::
CCubePrimitive(void)
    : position(CVector3::ZERO)
    , collision_pos(aqua::CVector3::ZERO)
    , width(0.0f)
    , height(0.0f)
    , depth(0.0f)
    , m_HRotate(0.0f)
    , m_VRotate(0.0f)
    , m_TRotate(0.0f)
    , color(aqua::CColor::WHITE)
    , spc_color(aqua::CColor::WHITE)
    , last_dire(COLL_DIRE::FRONT)
    , fill(false)
{
    // 手前
    index[0] = 0;
    index[1] = 1;
    index[2] = 2;

    index[3] = 3;
    index[4] = 2;
    index[5] = 1;

    // 右
    index[6] = 4;
    index[7] = 5;
    index[8] = 0;

    index[9] = 1;
    index[10] =0;
    index[11] =5;

    // 奥
    index[12] = 6;
    index[13] = 7;
    index[14] = 4;

    index[15] = 5;
    index[16] = 4;
    index[17] = 7;
     
    // 左
    index[18] = 2;
    index[19] = 3;
    index[20] = 6;

    index[21] =7;
    index[22] =6;
    index[23] =3;

    // 下
    index[24] =1;
    index[25] =5;
    index[26] =3;

    index[27] =7;
    index[28] =3;
    index[29] =5;

    // 上
    index[30] =4;
    index[31] =0;
    index[32] =6;

    index[33] =2;
    index[34] =6;
    index[35] =0;
}


void aqua::CCubePrimitive::Setup(const aqua::CVector3& center_pos, float width_, float height_, float depth_, const aqua::CColor& color_, const aqua::CColor& spc_color_, bool fill_)
{
    position = center_pos;
    width = width_;
    height = height_;
    depth = depth_;
    color = color_;
    spc_color = spc_color_;

    Transform();

    DrawPolygonIndexed3D(vertex, vertex_count, index, polygon_count, DX_NONE_GRAPH, false);
}

void aqua::CCubePrimitive::Transform(void)
{
    aqua::CMatrix mat;

    mat.RotationZ(aqua::DegToRad(m_TRotate));

    mat.RotationX(aqua::DegToRad(m_VRotate));

    mat.RotationY(aqua::DegToRad(m_HRotate));

    mat.Translate(position);

    float wid = width / 2;
    float hei = height / 2;
    float dep = depth / 2;
    COLOR_U8 dif_ = GetColorU8(color.red, color.green, color.blue, color.alpha);
    COLOR_U8 spc_ = GetColorU8(spc_color.red, spc_color.green, spc_color.blue, spc_color.alpha);

    vertex[0].pos = aqua::CVector3(wid, hei, -dep);       // 手前右上
    vertex[0].norm = aqua::CVector3(1.0f, 1.0f, -1.0f);

    vertex[1].pos = aqua::CVector3(wid, -hei, -dep);      // 手前右下
    vertex[1].norm = aqua::CVector3(1.0f, -1.0f, -1.0f);

    vertex[2].pos = aqua::CVector3(-wid, hei, -dep);      // 手前左上
    vertex[2].norm = aqua::CVector3(-1.0f, 1.0f, -1.0f);

    vertex[3].pos = aqua::CVector3(-wid, -hei, -dep);     // 手前左下
    vertex[3].norm = aqua::CVector3(-1.0f, -1.0f, -1.0f);


    vertex[4].pos =   aqua::CVector3(wid, hei, dep);        // 奥右上
    vertex[4].norm = aqua::CVector3(1.0f, 1.0f, 1.0f);

    vertex[5].pos =  aqua::CVector3(wid, -hei, dep);       // 奥右下
    vertex[5].norm = aqua::CVector3(1.0f, -1.0f, 1.0f);

    vertex[6].pos =  aqua::CVector3(-wid, hei, dep);       // 奥左上
    vertex[6].norm = aqua::CVector3(-1.0f, 1.0f, 1.0f);

    vertex[7].pos = aqua::CVector3(-wid, -hei, dep);      // 奥左下
    vertex[7].norm = aqua::CVector3(-1.0f, -1.0f, 1.0f);

    for (int i = 0; i < 8; i++)
    {
        vertex[i].pos = aqua::CVector3(vertex[i].pos) * mat;
        vertex[i].dif = dif_;
        vertex[i].spc = spc_;
        vertex[i].u = 0.0f;
        vertex[i].v = 0.0f;
        vertex[i].su = 0.0f;
        vertex[i].sv = 0.0f;
    }

}

/*
 *  描画
 */
void
aqua::CCubePrimitive::
Draw(void)
{
    Transform();

    // 非表示の時は描画しない
    if (!visible) return;

    DrawPolygonIndexed3D(vertex, vertex_count, index, polygon_count, DX_NONE_GRAPH, false);
}

bool aqua::CCubePrimitive::CheckCollision(CVector3& pointA, CVector3& pointB)
{
    last_dire = COLL_DIRE::FRONT;
    for (int i = 0; i < index_count;)
    {
        // vertexとindexを使って三角形の頂点を求めどれかに触れていればその時点でfor文を抜ける
        if (HitCheck_Line_Triangle(pointA, pointB, vertex[index[i]].pos, vertex[index[i + 1]].pos, vertex[index[i + 2]].pos).HitFlag == 1)
        {
            collision = true;
            return collision;
        }
        // iはインデックスの要素番号なので6刻みで調べている面が変わる→6で割り切れるタイミングで面が切り替わる
        if (i % 6)
            last_dire = (COLL_DIRE)((int)last_dire + 1);
        i += 3;
    }
    collision = false;
    return collision;
}

bool aqua::CCubePrimitive::CheckCollision(CVector3& center_pos, float r)
{
    for (int i = 0; i < index_count;)
    {
        // vertexとindexを使って三角形の頂点を求めどれかに触れていればその時点でfor文を抜ける
        if (HitCheck_Sphere_Triangle(center_pos,r, vertex[index[i]].pos, vertex[index[i + 1]].pos, vertex[index[i + 2]].pos)==1)
        {
            collision = true;
            return collision;
        }
        i += 3;
    }
    collision = false;
    return collision;
}

bool aqua::CCubePrimitive::CheckCollision(CVector3& positionA, CVector3& positionB, float r)
{
    collision = false;

    for (int i = 0; i < index_count;)
    {
        // vertexとindexを使って三角形の頂点を求めどれかに触れていればその時点でfor文を抜ける
        if (HitCheck_Capsule_Triangle(positionA, positionB, r, vertex[index[i]].pos, vertex[index[i + 1]].pos, vertex[index[i + 2]].pos) == 1)
        {
            collision = true;

            aqua::CVector3 coll_pos;
            coll_pos = ((aqua::CVector3)vertex[index[i]].pos + (aqua::CVector3)vertex[index[i + 1]].pos + (aqua::CVector3)vertex[index[i + 2]].pos) / 3.0f;
            
            float a = abs(aqua::CVector3::Length(positionA - coll_pos));
            float b = abs(aqua::CVector3::Length(positionA - collision_pos));
            if (a < b || collision_pos == aqua::CVector3::ZERO)
                collision_pos = coll_pos;


            //return collision;
        }
        i += 3;
    }
    return collision;
}
