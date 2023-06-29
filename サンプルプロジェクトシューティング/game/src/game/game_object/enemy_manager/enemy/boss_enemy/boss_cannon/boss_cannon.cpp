#include "../../../../game_object.h"
#include "../boss_enemy.h"
#include "boss_cannon.h"


CBossCannon::CBossCannon(aqua::IGameObject* parent)
	: CEnemy(parent, "BossCannon")
{
}

void CBossCannon::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)
{
	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
	// ���f���͉�
	m_Model.Load("data\\model\\fixed_enemy.mv1");
	m_Model.position = m_Position;

	m_BossEnemy = (CBossEnemy*)aqua::FindGameObject("BossEnemy");

	m_Cube.visible = false;
}

void CBossCannon::Update(void)
{
	CEnemy::Update();
	m_Cube.m_HRotate = m_Rotate;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CBossCannon::Draw(void)
{
	m_Model.Draw();
	CEnemy::Draw();
}

void CBossCannon::Finalize(void)
{
	CEnemy::Finalize();
	m_Model.Unload();
}

void CBossCannon::Move(void)
{
	// �v���C���[�Ǝ��g�̋���
	aqua::CVector3 v = m_Player->GetPosition() - m_Position;

	// �x�N�g���̃m�[�}���C�Y
	v.Normalize();

	// 2�_�����]�p�x�����߂�
	m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
}