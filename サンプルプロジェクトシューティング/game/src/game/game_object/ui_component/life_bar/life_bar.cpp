#include "../../game_object.h"
#include "life_bar.h"

CLifeBar::CLifeBar(aqua::IGameObject* parent)
	: IUIComponent(parent,"LifeBar")
	, m_Camera(nullptr)
	, m_GameMain(nullptr)
{
}

void CLifeBar::Initialize(void)
{
	m_Sprite[0].Create("data\\texture\\ui\\life_bar\\life_bar.png");
	m_Sprite[1].Create("data\\texture\\ui\\life_bar\\life_gage.png");

	// �Q�[�����C���V�[���擾
	m_GameMain = (CGameMain*)aqua::FindGameObject("GameMainScene");
	m_Camera = m_GameMain->GetCamera();

	m_Unit = (IUnit*)GetParent();
}

void CLifeBar::Update(void)
{
	// ���[���h���W���X�N���[�����W�ɕϊ����閲�̂悤�Ȋ֐�
	aqua::CVector3 pos = ConvWorldPosToScreenPos(m_Unit->GetPosition());
	
	CalcLifeBar();

	// �X�v���C�g�̒��S���W�����j�b�g�̃X�N���[�����W�ɍ��킹��
	m_Sprite[1].SetCenterPosition(aqua::CVector2(pos.x, pos.y - 30.0f));
	m_Sprite[0].position = m_Sprite[1].position;
}

void CLifeBar::Draw(void)
{
	m_Sprite[0].Draw();
	m_Sprite[1].Draw();

}

void CLifeBar::Finalize(void)
{
	m_Sprite[0].Delete();
	m_Sprite[1].Delete();
}

void CLifeBar::CalcLifeBar(void)
{
	float rect = m_Sprite[0].GetTextureWidth() / m_Unit->GetMaxLife();
	m_Sprite[0].rect.right = rect * m_Unit->GetLife();
}
