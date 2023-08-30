#include "../game_object.h"
#include "unit.h"

const float IUnit::m_beam_damage_interval =0.3f;

IUnit::
IUnit(aqua::IGameObject* parent, const std::string& object_name)
	: aqua::IGameObject(parent,object_name)
	, m_Height(0.0f)
	, m_Width(0.0f)
	, m_Depth(0.0f)
	, m_Speed(0.0f)
	, m_Angle(0.0f)
	, m_MaxLife(0)
	, m_Life(0)
	, m_DeadFlag(true)
	, m_MoveFlag(true)
	, m_LockON(false)
	, m_Rotate(0.0f)
	, m_Position(aqua::CVector3::ZERO)
	, m_Velocity(aqua::CVector3::ZERO)
	, m_EffectManager(nullptr)
	, m_SoundManager(nullptr)
	, m_BulletManager(nullptr)
	, m_StageManager(nullptr)
{
}

void IUnit::Initialize(aqua::CVector3 pop_pos, float wid, float hei, float dep, CStageManager* st_m , CBulletManager* bm)
{
	// �e���b���̐ݒ�
	m_Position = pop_pos;
	m_Width = wid;
	m_Height = hei;
	m_Depth = dep;
	m_BulletManager = bm;
	m_StageManager = st_m;
	m_DeadFlag = false;
	m_Color = aqua::CColor::BLACK;
	m_Cube.Setup(m_Position, m_Width, m_Height, m_Depth, m_Color);
	aqua::CreateGameObject<CLifeBar>(this);
	// �G�t�F�N�g�Ǘ��N���X��T�����ă|�C���^���󂯎��
	m_EffectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");
	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
	// �r�[���ɂ��_���[�W�̊Ԋu�p�^�C�}�[�̃Z�b�g�A�b�v
	m_BeamInterval.Setup(m_beam_damage_interval);

	m_Cube.visible = false;

	IGameObject::Initialize();
}

void IUnit::Draw(void)
{
	m_Cube.Draw();
	m_Model.Draw();
	IGameObject::Draw();
}

void IUnit::Finalize(void)
{
	m_Model.Unload();
	IGameObject::Finalize();
}

void IUnit::Update(void)
{
	Move();
	m_Cube.position = m_Position;

	IGameObject::Update();
}

bool IUnit::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere,int damage)
{
	// �e�̏��������g�Ɠ����Ȃ珈�����Ȃ�
	if (m_UnitType == type)
		return false;
	// �L���[�u�N���X�̃R���W�����֐��Ŕ���`�F�b�N
	if (m_Cube.CheckCollision(sphere.position, sphere.radius))
		// ����������_���[�W
		Damage(damage);
	return m_Cube.collision;
}

bool IUnit::CheckHitBeam(UNIT_TYPE type, aqua::CCapsulePrimitive capsule, int damage)
{
	// �r�[���_���[�W�Ԋu�p�^�C�}�[�̍X�V
	m_BeamInterval.Update();
	// �^�C�}�[���I�����Ă��Ȃ��܂��r�[���̏��������g�Ɠ����Ȃ珈�����Ȃ�
	if (!m_BeamInterval.Finished()|| m_UnitType == type)
		return false;
	// �L���[�u�N���X�̃R���W�����֐��Ŕ���`�F�b�N
	if (m_Cube.CheckCollision(capsule.Apos,capsule.Bpos,capsule.radius))
	{
		// ����������_���[�W
		Damage(damage);

		// ��e�G�t�F�N�g
		m_EffectManager->Create(EFFECT_ID::BEAM_HIT, m_Position, 0.0f, 8.0f);

		// �^�C�}�[�����Z�b�g
		m_BeamInterval.Reset();
	}
	return m_Cube.collision;
}

bool IUnit::GetDead(void)
{
	if (!this)
		return false;
	return m_DeadFlag;
}

void IUnit::Shot(void)
{
}

void IUnit::Move(void)
{
}

void IUnit::Damage(int damage)
{
	// ���C�t���_���[�W���l�����Z
	m_Life -= damage;


	// ���C�t��0�ȉ��ɂȂ����玀�S�������s��
	if (m_Life <= 0)
		Dead();
	else
		// 0�ȉ��łȂ���΃_���[�WSE���Đ����Ȃ�
		m_SoundManager->Play(SOUND_ID::s_DAMAGE);

}

void IUnit::Dead(void)
{
	m_DeadFlag = true;
	m_Cube.visible = false;

	// ���S�G�t�F�N�g���Đ�
	m_EffectManager->Create(EFFECT_ID::DEAD, m_Position);
	// SE���Đ�
	m_SoundManager->Play(SOUND_ID::s_DEAD);
}
