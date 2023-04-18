
#pragma once

#include"aqua.h"
#include"../camera_control/camera_control.h"

// �T���v���V�[��
class CSmpleScene : public aqua::IGameObject
{
public:

	// �R���X�g���N�^
	CSmpleScene(aqua::IGameObject* parent);

	// �f�X�g���N�^
	~CSmpleScene(void) = default;

	// ������
	void	Initialize(void)override;

	// �X�V
	void	Update(void)override;

	// �`��
	void	Draw(void)override;

	// ���
	void	Finalize(void)override;

private:
	aqua::CCamera	m_Camera;
	aqua::CModel	m_Model;
	aqua::CSpherePrimitive m_Sphere;
	aqua::CLinePrimitive3D m_Line;
	aqua::CCapsulePrimitive m_Capsule;
	aqua::CCubePrimitive	m_Cube;
	CCameraControl* m_CamControler;
};