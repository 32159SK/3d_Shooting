#include "../../../game_object.h"
#include "boss_cannon/boss_cannon.h"
#include "boss_enemy.h"

const float CBossEnemy::m_summon_interval = 20.0f;
const float CBossEnemy::m_all_range_ct = 10.0f;
const float CBossEnemy::m_dead_time = 6.0f;
const int CBossEnemy::m_cannon_count[] = { 2,4 };
const int CBossEnemy::m_position_pattern = 30;
const int CBossEnemy::m_max_summon = 10;
const aqua::CVector3 CBossEnemy::m_base_cannon_pos[] =
{
	 aqua::CVector3(-40.0f,0.0f,10.0f)
	,aqua::CVector3(40.0f,0.0f,10.0f)
	,aqua::CVector3(20.0f,0.0f,0.5f)
	,aqua::CVector3(-20.0f,0.0f,0.5f)
};
const std::string CBossEnemy::m_model_file_path = "data\\model\\boss_enemy.mv1";


CBossEnemy::CBossEnemy(aqua::IGameObject* parent)
	: CEnemy(parent, "BossEnemy")
	, m_PhaseLife{ 0 }
	, m_SummonCount(0)
	, m_AllRangeAttacking(false)
	, m_Phase(BOSS_PHASE::FIRST)
	, m_CannonPos{ aqua::CVector3::ZERO }
	, m_Cannon{ nullptr }
	, m_EnemyManager(nullptr)
{
}

void CBossEnemy::
Initialize(aqua::CVector3 pop_pos, ENEMY_INFO enemy_info, CStageManager* st_m, CBulletManager* bm)
{
	CEnemy::Initialize(pop_pos, enemy_info, st_m, bm);
	//m_Model.Load("data\\model\\fixed_enemy.mv1");
	//m_Model.position = m_Position;
	m_ShotBullet = BULLET_TYPE::PENETRATE;
	//m_Cube.visible = false;

	// �e(�G�Ǘ�)�N���X���擾
	m_EnemyManager = (CEnemyManager*)IGameObject::GetParent();

	// �Q�[�����C���V�[����T��
	m_GameMain = (CGameMain*)aqua::FindGameObject("GameMainScene");

	// �����^�C�}�[�̃Z�b�g
	m_SummonTimer.Setup(m_summon_interval);

	// AR�U��CT�v���^�C�}�[�̃Z�b�g
	m_AllRangeCT.Setup(m_all_range_ct);

	// ���S�^�C�}�[�̃Z�b�g
	m_DeadTimer.Setup(m_dead_time);


	for (int i = 0; i < BOSS_PHASE::DEAD; i++)
		m_PhaseLife[i] = m_Life;

	CannonSetUp();
}

void CBossEnemy::Update(void)
{
	IGameObject::Update();

	if (m_Player->GetTimeStop())
		return;
	Move();

	if (m_DeadFlag)
		return;
	m_ShotCT.Update();
	if (m_ShotCT.Finished())
	{
		Shot();
		m_ShotCT.Reset();
	}

	m_Life = m_PhaseLife[m_Phase];
	m_Cube.position = m_Position;
	m_Cube.m_HRotate = m_Rotate;
	//m_Model.rotation.y = aqua::DegToRad(m_Rotate);
}

void CBossEnemy::Draw(void)
{
	//m_Model.Draw();
	CEnemy::Draw();
}

void CBossEnemy::Finalize(void)
{
	CEnemy::Finalize();
	//m_Model.Unload();
}

bool CBossEnemy::CheckHitBullet(UNIT_TYPE type, aqua::CSpherePrimitive sphere, int damage)
{
	return CEnemy::CheckHitBullet(type, sphere, damage);
}

void CBossEnemy::SetCannonPosition(void)
{
	for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
		if (m_Cannon[i] && !m_Cannon[i]->GetDead())
			m_Cannon[i]->SetPosition(m_CannonPos[i]);
}

void CBossEnemy::Shot(void)
{
	if (m_AllRangeAttacking)
		return;

	switch (m_Phase)
	{
	case CBossEnemy::FIRST:	m_ShotBullet = BULLET_TYPE::NOMAL; break;
	case CBossEnemy::SECOND:m_ShotBullet = BULLET_TYPE::PENETRATE;	 break;
	}
	// CT���J���Ă���ΖC�Ɏˌ���������
	if (m_ShotCT.Finished())
	{
		for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
			if (m_Cannon[i] && !m_Cannon[i]->GetDead())
			{
				m_Cannon[i]->SetBulletType(m_ShotBullet);
				m_Cannon[i]->Shot();
			}
		CEnemy::Shot();
		m_ShotCT.Reset();
	}
}

void CBossEnemy::Move(void)
{
	if (m_DeadFlag && m_Phase != BOSS_PHASE::DEAD)
		return;
	// �{�X�̌`�Ԃɍ��킹������
	switch (m_Phase)
	{
	case CBossEnemy::FIRST: FirstPhase();	break;
	case CBossEnemy::SECOND:SecondPhase();	break;
	case CBossEnemy::DEAD:  Dead();			break;
	}

}

void CBossEnemy::Damage(int damage)
{
	m_PhaseLife[m_Phase] -= damage;

	// �`�Ԃ��Ƃ̃��C�t��0�ȉ��Ȃ�`�Ԉڍs
	if (m_PhaseLife[m_Phase] <= 0 )
		PhaseChange();
}

void CBossEnemy::Dead(void)
{
	if (!m_DeadFlag)
	{
		m_DeadFlag = true;
		// ���S���o
		m_EffectManager->Create(EFFECT_ID::BOSS_DEAD, m_Position);
		m_GameMain->SetGameClear(true);
	}
	
	// ���S�^�C�}�[�̍X�V
	m_DeadTimer.Update();

	//m_Cube.visible = false;
	if (m_DeadTimer.Finished())
		DeleteObject();
}

void CBossEnemy::FirstPhase(void)
{
	// �v���C���[�Ǝ��g�̋���
	aqua::CVector3 v = m_Player->GetPosition() - m_Position;

	// �x�N�g���̃m�[�}���C�Y
	v.Normalize();

	// 2�_�����]�p�x�����߂�
	m_Rotate = aqua::RadToDeg(atan2(v.x, v.z));

	// �s����g���Ďn�_�𒆐S�Ƃ�����]�������s���C�̍��W�����߂�
	aqua::CMatrix mat;
	mat.RotationY(aqua::DegToRad(m_Rotate));
	mat.Translate(m_Position);
	for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
		m_CannonPos[i] = -m_base_cannon_pos[i] * mat;
	SetCannonPosition();
}

void CBossEnemy::SecondPhase(void)
{
	// �^�C�}�[�̍X�V
	m_SummonTimer.Update();

	// �����^�C�}�[���I��
	if (m_SummonTimer.Finished())
		SummonEnemy();

	SetCannonPosition();

	// �I�[�������W�U�������Ă��Ȃ��Ȃ�ȉ��̏�����
	if (!m_AllRangeAttacking)
	{
		// 
		m_AllRangeCT.Update();

		for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
		{
			// �C�������Ă���Ȃ���W�ƒe�����������
			if (m_Cannon[i] && !m_Cannon[i]->GetDead())
				m_Cannon[i]->SetBulletType(m_ShotBullet);
		}
		// CT���I�����Ă�����I�[�������W�U�����s��
		if (m_AllRangeCT.Finished())
			AllRangeAttack();
	}
	else
	{
		for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
			// �A��^�C�~���O�͂ǂ���ꗥ�œ����Ȃ̂łǂꂩ��ł��I���Ă���΃I�[�������W�U���̏I��
			if (m_Cannon[i] && !m_Cannon[i]->GetDead())
				if (m_Cannon[i]->GetFinish())
					m_AllRangeAttacking = false;
	}
}

void CBossEnemy::PhaseChange(void)
{
	// ��Ԃ����S�Ȃ炱��ȏ�J�ڂ�����K�v�͂Ȃ�
	if (m_Phase == BOSS_PHASE::DEAD)
		return;
	// ���g�̌`�Ԃ����̌`�Ԃ֕ύX
	m_Phase = (BOSS_PHASE)((int)m_Phase + 1);

	if (m_Phase != BOSS_PHASE::DEAD)
	{
		m_Rotate = 180.0f;
		m_BulletManager->EnemyReset();
		m_BulletManager->SetEnemy(this);
		CannonSetUp();
	}

}

void CBossEnemy::CannonSetUp(void)
{
	// �C�̍Đ����E�ǉ��ƒe��̕ύX
	for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
	{
		if (m_Cannon[i])
			m_Cannon[i]->Dead();
		m_Cannon[i] = (CBossCannon*)m_EnemyManager->CreateBossParts(m_base_cannon_pos[i], ENEMY_ID::BOSS_CANNON);
		m_Cannon[i]->SetBulletType(m_ShotBullet);
		m_Cannon[i]->SetBossEnemy(this);
		m_Cannon[i]->SetCannonNumber(i);
		m_CannonPos[i] = m_Position + m_base_cannon_pos[i];
	}
}

void CBossEnemy::SummonEnemy(void)
{
	if (m_SummonCount < m_max_summon)
	{
		// �G��������
		m_EnemyManager->Create(m_CannonPos[0], ENEMY_ID::MOB);
		m_EnemyManager->Create(m_CannonPos[2], ENEMY_ID::MOB);
		m_SummonTimer.Reset();
		m_SummonCount += 2;
	}
}

void CBossEnemy::AllRangeAttack(void)
{
	m_AllRangeAttacking = true;
	// ���̎��_�Ń^�C�}�[�����Z�b�g(���̊֐����ēx�ĂԂ̂�h���ړI�AARA���̓^�C�}�[�̍X�V��������Ȃ��̂�CT�����͂Ȃ�)
	m_AllRangeCT.Reset();

	float shot_angle[4] = { 0.0f };

	for (;;)
	{
		for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
			// �����Ŋp�x�����
			shot_angle[i] = (float)aqua::Rand(360.0f / m_position_pattern);
		
		// �p�x���ǂ������ĂȂ����m�F����
		if (shot_angle[0] != shot_angle[1] && shot_angle[0] != shot_angle[2] && shot_angle[0] != shot_angle[3] &&
			shot_angle[1] != shot_angle[2] && shot_angle[1] != shot_angle[3] && shot_angle[2] != shot_angle[3])
			break;
	}


	// �����Ă���C�ɃI�[�������W�U����������
	for (int i = 0; i < m_cannon_count[m_Phase]; ++i)
		if (m_Cannon[i] && !m_Cannon[i]->GetDead())
		{
			m_Cannon[i]->SetBulletType(BULLET_TYPE::BEAM);
			m_Cannon[i]->SetAllRange(shot_angle[i]);
		}

}
