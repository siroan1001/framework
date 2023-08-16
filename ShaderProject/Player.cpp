#include "Player.h"
#include "ModelManager.h"
#include "SceneGame.h"
#include "Stage.h"
#include "Input.h"

Player::Player() : m_AIFlag(false)
{
	m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_PLAYER);
}

Player::~Player()
{
}

void Player::Update()
{
	if (IsKeyTrigger('W'))
	{
		m_PosInt.x++;
		m_PosInt.y--;
	}
	if (IsKeyTrigger('A'))
	{
		m_PosInt.x++;
		m_PosInt.y++;
	}
	if (IsKeyTrigger('S'))
	{
		m_PosInt.x--;
		m_PosInt.y++;
	}
	if (IsKeyTrigger('D'))
	{
		m_PosInt.x--;
		m_PosInt.y--;
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

void Player::SetPosition(DirectX::XMINT2 num)
{
	m_PosInt = num;
	Stage* stage = SceneGame::GetObj<Stage>("Stage");
	m_Pos = stage->GetPosition(m_PosInt);
	m_Pos.y = 0.5f;
}
