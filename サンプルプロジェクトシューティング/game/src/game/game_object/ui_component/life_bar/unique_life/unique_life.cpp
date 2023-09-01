#include "../../../game_object.h"
#include "unique_life.h"

CUniqueLifeBar::CUniqueLifeBar(aqua::IGameObject* parent)
	: CLifeBar(parent)
{
}

void CUniqueLifeBar::Initialize(void)
{
	m_Unit = (IUnit*)GetParent();

	// �Q�[���I�u�W�F�N�g�̖��O(�v���C���[�Ȃ�"Player")���擾
	m_UnitName = m_Unit->GetGameObjectName();

	// �擾�������O���p�X�Ɋ܂߂ăX�v���C�g�𐶐�
	m_Sprite[0].Create("data\\texture\\ui\\life_bar\\" + m_UnitName + "_life_bar.png");
	m_Sprite[1].Create("data\\texture\\ui\\life_bar\\" + m_UnitName + "_life_gauge.png");

	// �`��ʒu�̕ϐ�
	aqua::CVector2 pos = aqua::CVector2::ZERO;

	// ���O�ɉ����Ĉʒu�����߂�
	if (m_UnitName == "Player")
	{
		// �v���C���[�Ȃ��ʉE��
		pos.x = (float)aqua::GetWindowWidth() - m_Sprite[1].GetTextureWidth();
		pos.y = (float)aqua::GetWindowHeight() - m_Sprite[1].GetTextureHeight();
	}
	else
	{
		// �v���C���[�łȂ� �� �{�X�̃��C�t�o�[�Ȃ̂ŉ�ʏ㕔����
		pos.x = ((float)aqua::GetWindowWidth() - m_Sprite[1].GetTextureWidth()) / 2.0f;
	}
	// �X�v���C�g�ɕ`��ʒu����
	m_Sprite[1].position = pos;
	m_Sprite[0].position = pos;

}

void CUniqueLifeBar::Update(void)
{

}

void CUniqueLifeBar::CalcLifeBar(void)
{
	if (!this || m_Unit->GetDead())
		return;
	float rect = m_Sprite[0].GetTextureWidth() / m_Unit->GetMaxLife();
	// ���O�ɉ����Ĉʒu�����߂�
	if (m_UnitName == "Player")
	{
		float left = rect * (m_Unit->GetMaxLife() - m_Unit->GetLife());

		// �v���C���[�Ȃ獶����
		m_Sprite[0].rect.left = left;
		m_Sprite[0].position.x = m_Sprite[1].position.x + left;
	}
	else
		// �{�X�̃��C�t�o�[�͉E����
		m_Sprite[0].rect.right = rect * m_Unit->GetLife();
}

