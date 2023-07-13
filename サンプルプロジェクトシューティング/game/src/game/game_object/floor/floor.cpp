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
	// 渡された始点と終点で床モデルとの線分接触判定を行う
	m_Floor.CheckCollision(pointA, pointB);
	// 判定後の線分との接触座標を代入
	m_RaycastPos = m_Floor.GetLineCollPos();
}

