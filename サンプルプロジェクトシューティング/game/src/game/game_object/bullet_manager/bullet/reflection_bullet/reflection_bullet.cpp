#include "reflection_bullet.h"

CReflectionBullet::CReflectionBullet(aqua::IGameObject* parent)
	: IBullet(parent, "NomalBullet")
	, m_ReflectCount(0)
{
}

void CReflectionBullet::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user, CEffectManager* em)
{
	m_Model.Load("data\\model\\reflect_bullet.mv1");
	IBullet::Initialize(bullet_info, attri, pop_pos, front, user, em);
}


void CReflectionBullet::StageObjectHit(aqua::CCubePrimitive::COLL_DIRE c_dire)
{
	// 反射回数の上限を超えるなら反射させずにヒット関数を呼び出す
	if (m_ReflectCount > m_max_reflect_count)
		Hit();
	else // 反射回数を増加
		m_ReflectCount++;

	// 当たった壁の向きが前後ならZ軸を
	if (c_dire == aqua::CCubePrimitive::COLL_DIRE::FRONT
		|| c_dire == aqua::CCubePrimitive::COLL_DIRE::BACK)
		m_Dir.z *= -1.0f;
	// 当たった壁の向きが左右ならX軸を反転
	else if (c_dire == aqua::CCubePrimitive::COLL_DIRE::RIGHT
		|| c_dire == aqua::CCubePrimitive::COLL_DIRE::LEFT)
		m_Dir.x *= -1.0f;
}
