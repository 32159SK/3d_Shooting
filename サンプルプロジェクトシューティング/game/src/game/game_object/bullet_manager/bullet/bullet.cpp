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
	// �������̒i�K�ň�x�����X�V���ĂԂ��ƂŌ��������킹�鏈����������
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
	// �e�̈ړ�����
	m_Velocity = aqua::CVector3::ZERO;
	m_Velocity += m_Dir;
	m_Velocity = m_Velocity.Normalize();

	m_Velocity *= (m_Speed * to_delta);

	m_Position += m_Velocity;


	// �ړ����x�ɍ��킹�ĉ�]�p�x���Z�o
	m_Rotate = aqua::RadToDeg(atan2(m_Velocity.x, m_Velocity.z));
	// �����蔻��p�̋��N���X�̍��W�����킹��
	m_Sphere.position = m_Position;
	// ���f���̍��W�Ɖ�]�����킹��
	m_Model.position = m_Position;
	m_Model.rotation.y = aqua::DegToRad(m_Rotate);

	// �X�e�[�W�͈͊O�ɏo����폜
	if (m_Position.x < -250.0f || m_Position.x > 250.0f ||
		m_Position.z < -250.0f || m_Position.z > 250.0f)
		DeleteObject();
}

void IBullet::Finalize(void)
{
	// ���f���̉��
	m_Model.Unload();
}

void IBullet::Hit(void)
{
	// �G�t�F�N�g�Ǘ��N���X��null�łȂ��Ȃ璅�e�n�_�ɃG�t�F�N�g���o��
	if (m_EffectManager)
		m_EffectManager->Create(EFFECT_ID::HIT, m_Position);
	// ���g���폜
	DeleteObject();
}

void IBullet::StageObjectHit(aqua::CCubePrimitive::COLL_DIRE c_dire)
{
	// ��{�̃q�b�g�������s��
	Hit();
}

