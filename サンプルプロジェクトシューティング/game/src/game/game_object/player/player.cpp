#include "../game_object.h"
#include "player.h"

const float CPlayer::m_chage_shotCT = 0.5f;
const float CPlayer::m_the_world_time = 7.0f;
const float CPlayer::m_the_world_CT = 10.0f;

CPlayer::CPlayer(aqua::IGameObject* parent)
	: IUnit(parent, "Player")
	, m_AgoPosition(aqua::CVector3::ZERO)
	, m_Invincible(false)
	, m_TimeStop(false)
{
}

void CPlayer::Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, aqua::CColor color, CStageManager* st_m, CBulletManager* bm)
{
	IUnit::Initialize(pop_pos, wid, hei, dep, color, st_m, bm);
	m_UnitType = UNIT_TYPE::PLAYER;
	m_ShotBullet = BULLET_TYPE::NOMAL;
	m_BulletManager->SetPlayer(this);
	m_Speed = 1.0f;

	// 無敵時間の設定
	m_InvincibleTimer.Setup(2.0f);

	// 現在の弾種の仮表示
	m_DrawBT.Create(30.0f);
	m_DrawBT.position = aqua::CVector2(aqua::GetWindowWidth()/2,0.0f);

	// 最初からザ・ワールドを使えるようにタイマーの初期設定は0秒にする
	m_TheWorldTimer.Setup(0.0f);

	//
	m_ChageCT.Setup(m_chage_shotCT);
	m_ShotCT.Setup(0.5f);

	m_Cube.visible = false;

	m_Model.Load("data\\model\\player.mv1");
}

void CPlayer::Update(void)
{

	m_Cube.m_HRotate = m_Rotate;
	Shot();
	
	// 被弾後の無敵時間
	if (m_Invincible)
		m_InvincibleTimer.Update();
	if (m_InvincibleTimer.Finished())
	{
		m_Invincible = false;
		m_InvincibleTimer.Reset();
	}
	
	m_Invincible = true;

	// ザ・ワールド
	TheWorld();

	IUnit::Update();
	IGameObject::Update();

	m_Model.position = m_Cube.position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CPlayer::Draw(void)
{
	aqua::CVector3 front;
	
	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));

	switch (m_ShotBullet)
	{
	case BULLET_TYPE::NOMAL: m_DrawBT.text = "BULLET:NOMAL"; break;
	case BULLET_TYPE::FAST: m_DrawBT.text = "BULLET:FAST"; break;
	case BULLET_TYPE::MINE: m_DrawBT.text = "BULLET:MINE"; break;
	default:
		break;
	}

	m_DrawBT.Draw();
	m_Model.Draw();
	IUnit::Draw();
}

void CPlayer::Finalize(void)
{
	IUnit::Finalize();
	m_DrawBT.Delete();
	m_Model.Unload();
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

	// 弾の種類の切り替え
	if (m_ChageCT.Finished())
	{

		if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::UP) && m_ShotBullet != BULLET_TYPE::NOMAL)
		{
			// -1の弾に変更(例FAST→NOMAL)
			m_ShotBullet = (BULLET_TYPE)((int)m_ShotBullet - 1);
			m_ChageCT.Reset();
		}
		// ↓キー
		if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::DOWN) && (int)m_ShotBullet < (int)BULLET_TYPE::MAX - 1)
		{
			// +1の弾に変更(例NOMAL→FAST)
			m_ShotBullet = (BULLET_TYPE)((int)m_ShotBullet + 1);
			m_ChageCT.Reset();
		}
	}

	aqua::CVector3 front;

	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));

	if (m_ShotCT.Finished())
	{
		if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::SPACE))
		{
			// 自機の正面から球を撃つ
			m_BulletManager->Create(m_Position + front * 10, front * 10.5, m_UnitType, m_ShotBullet, this);
			m_ShotCT.Reset();
		}
		// ここでついでに敵が追尾する用のポジションを取っておく(時間停止していない場合)
		if (!m_TimeStop)
			m_AgoPosition = m_Position;
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


	//// 壁と当たってたらそこで止まる
	//if (m_StageManager->StageObjectCollision(m_Position, m_Position + m_Velocity * (m_Width / 2.0f)))
	//	return;

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

void CPlayer::TheWorld(void)
{
	// ザ・ワールド用タイマー
	m_TheWorldTimer.Update();
	// 停止時間切れの時は時止めを解除してタイマーをクールタイムとして再設定
	if (m_TimeStop&&m_TheWorldTimer.Finished())
	{
		m_TimeStop = false;
		m_TheWorldTimer.Setup(m_the_world_CT);
	}

	// 時が止まっていないかつタイマー終了→クールタイム開けなのでザ・ワールド使用可能
	if (!m_TimeStop && m_TheWorldTimer.Finished()&&
		aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Z))
	{
		m_TimeStop = true;
		m_TheWorldTimer.Setup(m_the_world_time);
	}
}
