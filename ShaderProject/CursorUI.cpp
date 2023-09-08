#include "CursorUI.h"

CursorUI::CursorUI()
{
	CreateTex("Assets/Texture/yazirusi.png");
	SetSize(DirectX::XMFLOAT2(25.0f, 25.0f));

	m_maxMove = 2.0f;
	m_CurentMove = 0.0f;
	m_AnimeFrame = 10.0f;
	m_MoveFlag = true;
	m_Rot = 0.0f;
	m_CurentNum = 0;
}

void CursorUI::Update()
{
	DirectX::XMFLOAT3 forward = GetForward();
	DirectX::XMFLOAT2 pos = m_Pos;
	m_CurentMove += m_maxMove / m_AnimeFrame;
	if (m_MoveFlag)
	{
		pos.x += forward.z * m_CurentMove;
		pos.y += forward.x * m_CurentMove;
	}
	else
	{
		pos.x -= forward.z * m_CurentMove;
		pos.y -= forward.x * m_CurentMove;
	}
	if (m_CurentMove >= m_maxMove)
	{
		m_CurentMove = 0.0f;
		m_MoveFlag ^= 1;
	}
	SetPos(pos);
}

DirectX::XMFLOAT3 CursorUI::GetForward()
{
	DirectX::XMFLOAT4X4 rot;
	DirectX::XMStoreFloat4x4(&rot,
		DirectX::XMMatrixRotationRollPitchYaw(0.0f, DirectX::XMConvertToRadians(m_Rot), 0.0f));

	DirectX::XMFLOAT3 forward;
	forward.x = rot._31;
	forward.y = rot._32;
	forward.z = rot._33;

	return forward;
}
