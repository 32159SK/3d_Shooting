#include "../../game_object.h"
#include "enemy.h"

const aqua::CVector3 CEnemy::m_surroundings[] =
{
	aqua::CVector3(1.0f,0.0f,0.0f),
	aqua::CVector3(0.0f,0.0f,-1.0f),
	aqua::CVector3(-1.0f,0.0f,0.0f),
	aqua::CVector3(0.0f,0.0f,1.0f),
};

CEnemy::CEnemy(aqua::IGameObject* parent, const std::string& object_name)
	: IUnit(parent,"Enemy")
{
}

void 
CEnemy::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m,CBulletManager* bm)
{
	// ��{�I�ȃ��j�b�g�̏����������N���X�̏��������Ăяo���čs��
	IUnit::Initialize(pop_pos, enemy_info.width, enemy_info.height, enemy_info.depth,st_m, bm);
	// �n���ꂽ���ŃX�e�[�^�X�����߂�
	m_MaxLife = enemy_info.life;
	m_Life = m_MaxLife;
	m_UnitType = UNIT_TYPE::ENEMY;
	m_ShotCT.Setup(enemy_info.shot_ct);
	m_Speed = enemy_info.speed;

	// ���˂̃^�C�~���O�����炷���߂ɗ����ł�����x�̂΂����^����
	float shot_time_rand = (float)aqua::Rand((int)ceil(enemy_info.shot_ct));
	m_ShotCT.SetTime(shot_time_rand);
}

void CEnemy::Update(void)
{
	IGameObject::Update();

	if (!m_MoveFlag)
		return;

	m_ShotCT.Update();
	if(m_ShotCT.Finished())
	{
		Shot();
		m_ShotCT.Reset();
	}
	Move();
}

void CEnemy::Draw(void)
{
	m_Cube.Draw();
	IGameObject::Draw();
}

void CEnemy::Finalize(void)
{
	IGameObject::Finalize();
}


void CEnemy::Shot(void)
{
	aqua::CVector3 front;

	// ��]�p�x���琳�ʂ����߂�
	front.x = sin(aqua::DegToRad(m_Rotate));
	front.z = cos(aqua::DegToRad(m_Rotate));

	// �e�̐���
	m_BulletManager->Create(m_Position, front, m_UnitType, m_ShotBullet, this);
	// SE���Đ�
	//m_SoundManager->Play(SOUND_ID::s_SHOT);
}
 
void CEnemy::Move(void)
{
	// �ړ����x�ɍ��킹�ĉ�]�p�x���Z�o
	m_Rotate = aqua::RadToDeg(atan2(m_Velocity.x, m_Velocity.z));
	m_Cube.m_HRotate = m_Rotate;

	m_Position += m_Velocity;

	m_Cube.position = m_Position;
}

void CEnemy::Dead(void)
{
	IUnit::Dead();
	m_BulletManager->EnemyReset(this);
	DeleteObject();
}
