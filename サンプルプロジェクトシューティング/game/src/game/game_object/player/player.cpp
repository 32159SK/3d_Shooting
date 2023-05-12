#include "../game_object.h"
#include "player.h"

const float CPlayer::m_chage_shotCT = 0.5f;

CPlayer::CPlayer(aqua::IGameObject* parent)
	: IUnit(parent, "Player")
	, m_AgoPosition(aqua::CVector3::ZERO)
	, m_Invincible(false)
{
}

void CPlayer::Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CBulletManager* bm)
{
	IUnit::Initialize(pop_pos, wid, hei, dep, color, bm);
	m_UnitType = UNIT_TYPE::PLAYER;
	m_ShotBullet = BULLET_TYPE::NOMAL;
	m_BulletManager->SetPlayer(this);
	m_Speed = 1.0f;

	// ñ≥ìGéûä‘ÇÃê›íË
	m_InvincibleTimer.Setup(2.0f);

	// åªç›ÇÃíeéÌÇÃâºï\é¶
	m_DrawBT.Create(30.0f);
	m_DrawBT.position = aqua::CVector2(aqua::GetWindowWidth()/2,0.0f);


	m_ChageCT.Setup(m_chage_shotCT);
	m_ShotCT.Setup(0.5f);
}

void CPlayer::Update(void)
{

	m_Cube.m_HRotate = m_Rotate;
	Shot();
	
	if (m_Invincible)
		m_InvincibleTimer.Update();
	if (m_InvincibleTimer.Finished())
	{
		m_Invincible = false;
		m_InvincibleTimer.Reset();
	}

	IUnit::Update();
	IGameObject::Update();
}

void CPlayer::Draw(void)
{
	aqua::CVector3 front;
	
	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));

	m_Line.pointA = m_Position;
	m_Line.pointB = m_Position + (front * 20.0f);
	m_Line.Draw();

	switch (m_ShotBullet)
	{
	case BULLET_TYPE::NOMAL: m_DrawBT.text = "BULLET:NOMAL"; break;
	case BULLET_TYPE::FAST: m_DrawBT.text = "BULLET:FAST"; break;
	case BULLET_TYPE::MINE: m_DrawBT.text = "BULLET:MINE"; break;
	default:
		break;
	}

	m_DrawBT.Draw();
	IUnit::Draw();
}

void CPlayer::Finalize(void)
{
	IUnit::Finalize();
	m_DrawBT.Delete();
}

bool CPlayer::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)
{
	if (m_Invincible)
		return false;

	if (IUnit::CheckHitBullet(type, sphere, damage))
	{
		m_Invincible = true;
		return true;
	}
	else
		return false;
}


void CPlayer::Shot(void)
{
	m_ChageCT.Update();
	m_ShotCT.Update();

	// íeÇÃéÌóﬁÇÃêÿÇËë÷Ç¶
	if (m_ChageCT.Finished())
	{

		if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::UP) && m_ShotBullet != BULLET_TYPE::NOMAL)
		{
			// -1ÇÃíeÇ…ïœçX(ó·FASTÅ®NOMAL)
			m_ShotBullet = (BULLET_TYPE)((int)m_ShotBullet - 1);
			m_ChageCT.Reset();
		}
		// Å´ÉLÅ[
		if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::DOWN) && (int)m_ShotBullet < (int)BULLET_TYPE::MAX - 1)
		{
			// +1ÇÃíeÇ…ïœçX(ó·NOMALÅ®FAST)
			m_ShotBullet = (BULLET_TYPE)((int)m_ShotBullet + 1);
			m_ChageCT.Reset();
		}
	}

	aqua::CVector3 front;

	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));

	if (m_ShotCT.Finished())
	{
		// Ç±Ç±Ç≈Ç¬Ç¢Ç≈Ç…ìGÇ™í«îˆÇ∑ÇÈópÇÃÉ|ÉWÉVÉáÉìÇéÊÇ¡ÇƒÇ®Ç≠
		m_AgoPosition = m_Position;
		if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::SPACE))
		{
			m_BulletManager->Create(m_Position + front, front * 1.5, m_UnitType, m_ShotBullet, this);
			m_ShotCT.Reset();
		}
	}
}

void CPlayer::Move(void)
{
	using namespace aqua::keyboard;
	const float to_delta = 60.0f * aqua::GetDeltaTime();

	m_Velocity = aqua::CVector3::ZERO;


	if (Button(KEY_ID::W)) m_Velocity += aqua::CVector3(0.0f, 0.0f, 1.0f);
	if (Button(KEY_ID::S)) m_Velocity -= aqua::CVector3(0.0f, 0.0f, 1.0f);
	if (Button(KEY_ID::A)) m_Velocity -= aqua::CVector3(1.0f, 0.0f, 0.0f);
	if (Button(KEY_ID::D)) m_Velocity += aqua::CVector3(1.0f, 0.0f, 0.0f);

	if (Button(KEY_ID::RIGHT)) m_Rotate += 2.0f;
	if (Button(KEY_ID::LEFT)) m_Rotate -= 2.0f;

	m_Velocity = m_Velocity.Normalize();
	m_Velocity *= (m_Speed * to_delta);
	m_Position += m_Velocity;
	AQUA_DEBUG_LOG("X:" + std::to_string(m_Position.x) + ",Z" + std::to_string(m_Position.z));
}

void CPlayer::Damage(int damage)
{
	IUnit::Damage(damage);
	m_Cube.color.alpha -= m_Cube.color.alpha / m_max_life;
}

void CPlayer::Dead(void)
{
	IUnit::Dead();
}
