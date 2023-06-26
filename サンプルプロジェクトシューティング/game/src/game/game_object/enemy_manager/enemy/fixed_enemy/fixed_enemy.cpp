#include "../../../game_object.h"
#include "fixed_enemy.h"

const float CFixedEnemy::m_capture_range = 100.0f;

CFixedEnemy::CFixedEnemy(aqua::IGameObject* parent)
	: CEnemy(parent)
{
}

void CFixedEnemy::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)
{
	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
	m_Model.Load("data\\model\\fixed_enemy.mv1");
	m_Model.position = m_Position;
	m_ShotBullet = BULLET_TYPE::PENETRATE;
	m_Cube.visible = false;
}

void CFixedEnemy::Update(void)
{
	CEnemy::Update();
	m_Cube.m_HRotate = m_Rotate;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CFixedEnemy::Draw(void)
{
	m_Model.Draw();
	CEnemy::Draw();
}

void CFixedEnemy::Finalize(void)
{
	CEnemy::Finalize();
	m_Model.Unload();
}

void CFixedEnemy::Shot(void)
{

	aqua::CVector3 front;

	CEnemy::Shot();

}

void CFixedEnemy::Move(void)
{
	// プレイヤーと自身の距離
	aqua::CVector3 v = m_Player->GetPosition() - m_Position;

	// 一度でも捕捉すれば死ぬまでこちらを向く
	if (m_capture_range > abs(aqua::CVector3::Length(v)))
		m_Capture = true;
	else if (!m_Capture)
		return;

	// ベクトルのノーマライズ
	v.Normalize();

	// 2点から回転角度を求める
	m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));
}
