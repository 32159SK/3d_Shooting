#include "floor.h"

CFloor::CFloor(aqua::IGameObject* parent)
	: IGameObject(parent,"Floor")
{
}

void CFloor::Initialize(void)
{
	m_Floor.Load("data\\model\\Plane.mv1");
	m_Floor.position = aqua::CVector3::ZERO;
	m_Floor.position.y = -10.0f;

	m_Floor.scale = aqua::CVector3(0.5f, 0.5f, 0.5f);


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

void CFloor::Raycast(aqua::CVector3 pointA, aqua::CVector3 pointB)
{
	// �n���ꂽ�n�_�ƏI�_�ŏ����f���Ƃ̐����ڐG������s��
	m_Floor.CheckCollision(pointA, pointB);
	// �����̐����Ƃ̐ڐG���W����
	m_RaycastPos = m_Floor.GetLineCollPos();
}

