#include "Player.h"
#include "ModelManager.h"
#include "SceneGame.h"
#include "Stage.h"
#include "Input.h"

Player::Player() : m_AIFlag(false), m_MoveFlag(false)
{
	m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_PLAYER);
}

Player::~Player()
{
}

void Player::Update()
{
	if (!m_MoveFlag)
	{
		if (IsKeyPress('W') && IsKeyPress('S') || IsKeyPress('A') && IsKeyPress('D')) return;

		if (IsKeyPress('W') && IsKeyPress('A'))
		{
			m_PosInt.x++;
			m_MoveFlag = true;
		}
		if (IsKeyPress('W') && IsKeyPress('D'))
		{
			m_PosInt.y--;
			m_MoveFlag = true;
		}
		if (IsKeyPress('S') && IsKeyPress('A'))
		{
			m_PosInt.y++;
			m_MoveFlag = true;
		}
		if (IsKeyPress('S') && IsKeyPress('D'))
		{
			m_PosInt.x--;
			m_MoveFlag = true;
		}

		if (m_PosInt.x > 5)
		{
			m_PosInt.x = 5;
		}
		else if (m_PosInt.x < 0)
		{
			m_PosInt.x = 0;
		}
		if (m_PosInt.y > 5)
		{
			m_PosInt.y = 5;
		}
		else if (m_PosInt.y < 0)
		{
			m_PosInt.y = 0;
		}

		SetPosition(m_PosInt);
	}
	else
	{
		if (IsKeyRelease('W') || IsKeyRelease('A') || IsKeyRelease('S') || IsKeyRelease('D'))
		{
			m_MoveFlag = false;
		}
	}
}

void Player::SetPosition(DirectX::XMINT2 num)
{
	m_PosInt = num;
	Stage* stage = SceneGame::GetObj<Stage>("Stage");
	m_Pos = stage->GetPosition(m_PosInt);
	m_Pos.y = 0.5f;
}
