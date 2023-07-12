#include "../../game_object.h"
#include "lockon_marker.h"

CLockOnMarker::CLockOnMarker(aqua::IGameObject* parent)
	: IUIComponent(parent,"LockOnMarker")
{
}

void CLockOnMarker::Initialize(void)
{
	// �摜�̐���
	m_Sprite.Create("data\\texture\\ui\\lock_on.png");

	// �Q�[�����C���V�[���擾
	m_GameMain = (CGameMain*)aqua::FindGameObject("GameMainScene");
	// �Q�[�����C���V�[������J�����̃|�C���^���擾
	m_Camera = m_GameMain->GetCamera();
	// �e�N���X���g�p�҂Ƃ��ă|�C���^���擾
	m_User = (IUnit*)GetParent();
}

void CLockOnMarker::Update(void)
{
	// �Ώۂ�null�܂��̓��b�N�I�����Ă��Ȃ��Ȃ珈�����Ȃ�
	if (!m_Target || !m_User->GetLockOnFlag())
		return;

	// ���[���h���W���X�N���[�����W�ɕϊ����閲�̂悤�Ȋ֐�
	aqua::CVector3 pos = ConvWorldPosToScreenPos(m_Target->GetPosition());

	// �X�v���C�g�̒��S���W�����b�N�I�����Ă���G�̃X�N���[�����W�ɍ��킹��
	m_Sprite.SetCenterPosition(aqua::CVector2(pos.x, pos.y));
}

void CLockOnMarker::Draw(void)
{
	// �Ώۂ�null�łȂ����g�p�҂����b�N�I����
	if (m_Target && m_User->GetLockOnFlag())
		m_Sprite.Draw();
}

void CLockOnMarker::Finalize(void)
{
	// �X�v���C�g�̍폜
	m_Sprite.Delete();
}
