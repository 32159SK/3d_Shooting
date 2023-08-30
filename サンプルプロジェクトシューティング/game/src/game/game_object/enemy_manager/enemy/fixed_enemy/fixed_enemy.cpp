#include "../../../game_object.h"
#include "fixed_enemy.h"

const float CFixedEnemy::m_capture_range = 100.0f;

CFixedEnemy::CFixedEnemy(aqua::IGameObject* parent)
	: CEnemy(parent, "FixedEnemy")
{
}

void CFixedEnemy::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)
{
	m_Model.Load("data\\model\\fixed_enemy.mv1");
	m_ShotBullet = BULLET_TYPE::BEAM;

	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
}

void CFixedEnemy::Update(void)
{
	CEnemy::Update();
	m_Cube.m_HRotate = m_Rotate;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CFixedEnemy::Shot(void)
{
	// �⑫���Ă���Ύˌ�
	if (m_Capture)
		CEnemy::Shot();
}

void CFixedEnemy::Move(void)
{

	// �v���C���[�Ǝ��g�̋���
	aqua::CVector3 v = m_Player->GetPosition() - m_Position;

	// ��x�ł��ߑ�����Ύ��ʂ܂ł����������
	if (m_capture_range > abs(aqua::CVector3::Length(v)))
		m_Capture = true;
	else if (!m_Capture)
		return;

	// �x�N�g���̃m�[�}���C�Y
	v.Normalize();

	// 2�_�����]�p�x�����߂�
	m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
}
