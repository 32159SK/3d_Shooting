#include "floor.h"

CFloor::CFloor(aqua::IGameObject* parent)
	: IGameObject(parent)
{
}

void CFloor::Initialize(void)
{
	m_Floor.Load("data\\model\\Plane.mv1");
	m_Floor.position = aqua::CVector3::ZERO;
	m_Floor.position.y = -10.0f;

}

void CFloor::Update(void)
{
}

void CFloor::Draw(void)
{
	m_Floor.Draw();
}

void CFloor::Finalize(void)
{
	m_Floor.Unload();
}
