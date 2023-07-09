#include "CameraDCC.h"
#include "Input.h"


enum CameraDCCKind
{
	CAM_DCC_NONE,
	CAM_DCC_ORBIT,
	CAM_DCC_TRACK,
	CAM_DCC_DOLLY,
	CAM_DCC_FLIGHT,
};

CameraDCC::CameraDCC()
	: m_state(CAM_DCC_NONE)
	, m_oldPos{ 0, 0 }
{
}
CameraDCC::~CameraDCC()
{
}
void CameraDCC::Update()
{
	UpdateState();
	if (m_state == CAM_DCC_NONE) return;

	Argument arg;
	// �}�E�X�ړ���
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	arg.mouseMove = DirectX::XMFLOAT2((float)cursorPos.x - m_oldPos.x, (float)cursorPos.y - m_oldPos.y);
	m_oldPos = cursorPos;
	// �J�������
	arg.vCamPos					= DirectX::XMLoadFloat3(&m_pos);
	arg.vCamLook				= DirectX::XMLoadFloat3(&m_look);
	DirectX::XMVECTOR vCamUp	= DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&m_up));
	DirectX::XMVECTOR vFront	= DirectX::XMVectorSubtract(arg.vCamLook, arg.vCamPos);
	// �J�����p��
	arg.vCamFront	= DirectX::XMVector3Normalize(vFront);
	arg.vCamSide	= DirectX::XMVector3Normalize(DirectX::XMVector3Cross(vCamUp, arg.vCamFront));
	arg.vCamUp		= DirectX::XMVector3Normalize(DirectX::XMVector3Cross(arg.vCamFront, arg.vCamSide));
	// �t�H�[�J�X����
	DirectX::XMStoreFloat(&arg.focus, DirectX::XMVector3Length(vFront));

	switch (m_state)
	{
	case CAM_DCC_ORBIT:		UpdateOrbit(arg);	break;
	case CAM_DCC_TRACK:		UpdateTrack(arg);	break;
	case CAM_DCC_DOLLY:		UpdateDolly(arg);	break;
	case CAM_DCC_FLIGHT:	UpdateFlight(arg);	break;
	}
}
void CameraDCC::UpdateState()
{
	CameraDCCKind prev = (CameraDCCKind)m_state;
	if (IsKeyPress(VK_MENU))
	{
		m_state = CAM_DCC_NONE;
		if (IsKeyPress(VK_LBUTTON)) m_state = CAM_DCC_ORBIT;
		if (IsKeyPress(VK_MBUTTON)) m_state = CAM_DCC_TRACK;
		if (IsKeyPress(VK_RBUTTON)) m_state = CAM_DCC_DOLLY;
	}
	else if (IsKeyPress(VK_RBUTTON))
	{
		m_state = CAM_DCC_FLIGHT;
	}
	else
	{
		m_state = CAM_DCC_NONE;
	}
	if (prev != m_state)
	{
		GetCursorPos(&m_oldPos);
	}
}
void CameraDCC::UpdateOrbit(Argument& arg)
{
	// �}�E�X�̈ړ��� / ��ʃT�C�Y �̔䗦����A��ʑS�̂łǂꂾ����]���邩�w�肷��B
	float angleX =  360.0f * arg.mouseMove.x / 1280.0f;
	float angleY =  180.0f * arg.mouseMove.y / 720.0f;

	// Y����]�ŃJ�����̉�������]
	DirectX::XMMATRIX matRotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angleX));
	DirectX::XMVECTOR vAxis = DirectX::XMVector3Normalize(DirectX::XMVector3TransformCoord(arg.vCamSide, matRotY));

	// ��]��̎��ŏc��]
	DirectX::XMMATRIX matRotSide = DirectX::XMMatrixRotationAxis(vAxis, DirectX::XMConvertToRadians(angleY));
	DirectX::XMVECTOR vRelative = DirectX::XMVectorScale(arg.vCamFront, arg.focus);
	vRelative = DirectX::XMVector3TransformCoord(vRelative, matRotY * matRotSide);

	// �J�������W�X�V
	DirectX::XMStoreFloat3(&m_pos, DirectX::XMVectorSubtract(arg.vCamLook, vRelative));

	// �A�b�v�x�N�g���X�V
	DirectX::XMStoreFloat3(&m_up, DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMVector3Normalize(vRelative), vAxis)));

}
void CameraDCC::UpdateTrack(Argument& arg)
{
	// ����A�A���B�Ƃ���O�p�`�ɂ��� tan�� = A / B�����藧��
	// ��L�������ƂɊ���o�������i�̍������A�ړ��� / ��ʃT�C�Y �̔䗦����A�ړ��ʂƂ��ċ��߂�
	float farScreenHeight = tanf(m_fovy * 0.5f) * m_far;
	float screenRateW = arg.mouseMove.x / 640.0f;
	float screenRateH = arg.mouseMove.y / 360.0f;
	float farMoveX = -farScreenHeight * screenRateW * m_aspect;
	float farMoveY = farScreenHeight * screenRateH;

	// �J�����̎p�������ƂɈړ�
	float rate = arg.focus / m_far;
	DirectX::XMVECTOR vCamMove = DirectX::XMVectorZero();
	vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorScale(arg.vCamSide, farMoveX * rate));
	vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorScale(arg.vCamUp, farMoveY * rate));
	DirectX::XMStoreFloat3(&m_pos, DirectX::XMVectorAdd(arg.vCamPos, vCamMove));
	DirectX::XMStoreFloat3(&m_look, DirectX::XMVectorAdd(arg.vCamLook, vCamMove));
}
void CameraDCC::UpdateDolly(Argument& arg)
{
	float rate = arg.focus / m_far;
	DirectX::XMVECTOR vMove = DirectX::XMVectorScale(arg.vCamFront, m_far * 0.01f * rate * (arg.mouseMove.x + arg.mouseMove.y));
	DirectX::XMStoreFloat3(&m_pos, DirectX::XMVectorAdd(arg.vCamPos, vMove));
}
void CameraDCC::UpdateFlight(Argument& arg)
{
	// �}�E�X�̈ړ��� / ��ʃT�C�Y �̔䗦����A��ʑS�̂łǂꂾ����]���邩�w�肷��B
	float angleX = 360.0f * arg.mouseMove.x / 1280.0f;
	float angleY = 180.0f * arg.mouseMove.y / 720.0f;

	// ����]
	DirectX::XMMATRIX matUpRot = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angleX));
	DirectX::XMVECTOR vSideAxis = DirectX::XMVector3Normalize(DirectX::XMVector3TransformCoord(arg.vCamSide, matUpRot));

	// �c��]
	DirectX::XMMATRIX matSideRot = DirectX::XMMatrixRotationAxis(vSideAxis, DirectX::XMConvertToRadians(angleY));
	DirectX::XMVECTOR vFrontAxis = DirectX::XMVector3Normalize(DirectX::XMVector3TransformCoord(arg.vCamFront, matUpRot * matSideRot));

	// �L�[���͂ňړ�
	DirectX::XMVECTOR vCamMove = DirectX::XMVectorZero();
	if (IsKeyPress('W')) vCamMove = DirectX::XMVectorAdd(vCamMove, vFrontAxis);
	if (IsKeyPress('S')) vCamMove = DirectX::XMVectorSubtract(vCamMove, vFrontAxis);
	if (IsKeyPress('A')) vCamMove = DirectX::XMVectorSubtract(vCamMove, vSideAxis);
	if (IsKeyPress('D')) vCamMove = DirectX::XMVectorAdd(vCamMove, vSideAxis);
	if (IsKeyPress('Q')) vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	if (IsKeyPress('E')) vCamMove = DirectX::XMVectorAdd(vCamMove, DirectX::XMVectorSet(0.0f,-1.0f, 0.0f, 0.0f));
	vCamMove = DirectX::XMVectorScale(vCamMove, 0.1f);

	// �X�V
	DirectX::XMVECTOR vCamPos = DirectX::XMVectorAdd(arg.vCamPos, vCamMove);
	DirectX::XMStoreFloat3(&m_pos, vCamPos);
	DirectX::XMStoreFloat3(&m_look, DirectX::XMVectorAdd(vCamPos, DirectX::XMVectorScale(vFrontAxis, arg.focus)));
	DirectX::XMStoreFloat3(&m_up, DirectX::XMVector3Normalize(DirectX::XMVector3Cross(vFrontAxis, vSideAxis)));
}