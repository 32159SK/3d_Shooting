#include "reflection_bullet.h"

CReflectionBullet::CReflectionBullet(aqua::IGameObject* parent)
	: IBullet(parent, "NomalBullet")
	, m_ReflectCount(0)
{
}

void CReflectionBullet::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user)
{
	IBullet::Initialize(bullet_info, attri, pop_pos, front, user);
	m_Sphere.visible = false;
	m_Model.Load("data\\model\\reflect_bullet.mv1");
	Update();
}

void CReflectionBullet::Update(void)
{
	IBullet::Update();
	m_Model.position = m_Position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CReflectionBullet::Draw(void)
{
	IBullet::Draw();
	m_Model.Draw();
}

void CReflectionBullet::Finalize(void)
{
	IBullet::Finalize();
	m_Model.Unload();
}

void CReflectionBullet::StageObjectHit(aqua::CCubePrimitive::COLL_DIRE c_dire)
{
	// ���ˉ񐔂̏���𒴂���Ȃ甽�˂������Ƀq�b�g�֐����Ăяo��
	if (m_ReflectCount > m_max_reflect_count)
		Hit();
	else // ���ˉ񐔂𑝉�
		m_ReflectCount++;

	// ���������ǂ̌������O��Ȃ�Z����
	if (c_dire == aqua::CCubePrimitive::COLL_DIRE::FRONT
		|| c_dire == aqua::CCubePrimitive::COLL_DIRE::BACK)
		m_Dir.z *= -1.0f;
	// ���������ǂ̌��������E�Ȃ�X���𔽓]
	else if (c_dire == aqua::CCubePrimitive::COLL_DIRE::RIGHT
		|| c_dire == aqua::CCubePrimitive::COLL_DIRE::LEFT)
		m_Dir.x *= -1.0f;

}
