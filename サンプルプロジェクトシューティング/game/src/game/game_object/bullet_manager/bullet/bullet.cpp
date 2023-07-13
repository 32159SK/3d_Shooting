#include "bullet.h"

IBullet::IBullet(aqua::IGameObject* parent, const std::string& object_name)
	: IGameObject(parent, object_name, "Bullet")
	, m_Damage(0)
	, m_Rotate(0.0f)
	, m_Radius(0.0f)
	, m_Speed(0.0f)
	, m_Position(aqua::CVector3::ZERO)
	, m_Dir(aqua::CVector3::ZERO)
	, m_StartPos(aqua::CVector3::ZERO)
	, m_Attri(UNIT_TYPE::PLAYER)
	, m_EffectManager(nullptr)
{
}

void IBullet::Initialize(BULLET_INFO bullet_info, UNIT_TYPE attri, aqua::CVector3 pop_pos, aqua::CVector3 front, IUnit* user,CEffectManager* em)
{
	m_Attri = attri;
	m_Position = pop_pos;
	m_Dir = front;
	m_Damage = bullet_info.damage;
	m_Speed = bullet_info.speed;
	m_Radius = bullet_info.radius;
	m_EffectManager = em;

	m_StartPos = m_Position;
	m_Sphere.Setup(m_Position, m_Radius);
	m_Sphere.visible = false;
	m_Model.position = m_Position;
	// 初期化の段階で一度だけ更新を呼ぶことで向きを合わせる処理をさせる
	Update();
}

void IBullet::Draw(void)
{
	m_Sphere.Draw();
	m_Model.Draw();
}

void IBullet::Update(void)
{
	const float to_delta = 60.0f * aqua::GetDeltaTime();
	// 弾の移動処理
	m_Velocity = aqua::CVector3::ZERO;
	m_Velocity += m_Dir;
	m_Velocity = m_Velocity.Normalize();

	m_Velocity *= (m_Speed * to_delta);

	m_Position += m_Velocity;


	// 移動速度に合わせて回転角度を算出
	m_Rotate = aqua::RadToDeg(atan2(m_Velocity.x, m_Velocity.z));
	// 当たり判定用の球クラスの座標を合わせる
	m_Sphere.position = m_Position;
	// モデルの座標と回転を合わせる
	m_Model.position = m_Position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);

	// ステージ範囲外に出たら削除
	if (m_Position.x < -250.0f || m_Position.x > 250.0f ||
		m_Position.z < -250.0f || m_Position.z > 250.0f)
		DeleteObject();
}

void IBullet::Finalize(void)
{
	// モデルの解放
	m_Model.Unload();
}

void IBullet::Hit(void)
{
	// エフェクト管理クラスがnullでないなら着弾地点にエフェクトを出す
	if (m_EffectManager)
		m_EffectManager->Create(EFFECT_ID::HIT, m_Position);
	// 自身を削除
	DeleteObject();
}

void IBullet::StageObjectHit(aqua::CCubePrimitive::COLL_DIRE c_dire)
{
	// 基本のヒット処理を行う
	Hit();
}

