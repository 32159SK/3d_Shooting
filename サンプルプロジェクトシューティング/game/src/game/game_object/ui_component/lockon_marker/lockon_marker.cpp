#include "../../game_object.h"
#include "lockon_marker.h"

CLockOnMarker::CLockOnMarker(aqua::IGameObject* parent)
	: IUIComponent(parent,"LockOnMarker")
{
}

void CLockOnMarker::Initialize(void)
{
	m_Sprite.Create("data\\texture\\ui\\lock_on.png");

	// �Q�[�����C���V�[���擾
	m_GameMain = (CGameMain*)aqua::FindGameObject("GameMainScene");
	m_Camera = m_GameMain->GetCamera();

	m_Player = (CPlayer*)GetParent();
}

void CLockOnMarker::Update(void)
{
	// �G��null�܂��̓��b�N�I�����Ă��Ȃ��Ȃ珈�����Ȃ�
	if (!m_LockOnEnemy || !m_Player->GetLockOnFlag())
		return;

	// ���[���h���W���X�N���[�����W�ɕϊ����閲�̂悤�Ȋ֐�
	aqua::CVector3 pos = ConvWorldPosToScreenPos(m_LockOnEnemy->GetPosition());

	// �X�v���C�g�̒��S���W�����b�N�I�����Ă���G�̃X�N���[�����W�ɍ��킹��
	m_Sprite.SetCenterPosition(aqua::CVector2(pos.x, pos.y));
}

void CLockOnMarker::Draw(void)
{
	if (m_LockOnEnemy && m_Player->GetLockOnFlag())
		m_Sprite.Draw();
}

void CLockOnMarker::Finalize(void)
{
	m_Sprite.Delete();
}
