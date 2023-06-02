
#include "../../game_object.h"
#include "skill_icon.h"

CSkillIcon::CSkillIcon(aqua::IGameObject* parent)
	: IUIComponent(parent, "Rader")
	, m_Player(nullptr)
{
}

void CSkillIcon::Initialize(CPlayer* player)
{
	m_Player = player;

}

void CSkillIcon::Update(void)
{
}

void CSkillIcon::Draw(void)
{
}

void CSkillIcon::Finalize(void)
{
}

