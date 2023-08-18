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
	if (!m_AIFlag)
	{
		if (!m_MoveFlag)
		{
			DirectX::XMINT2 posint = m_PosInt;

			if (IsKeyPress('W') && IsKeyPress('S') || IsKeyPress('A') && IsKeyPress('D')) return;

			if (IsKeyPress('W') && IsKeyPress('A'))
			{
				posint.x++;
				m_MoveFlag = true;
			}
			if (IsKeyPress('W') && IsKeyPress('D'))
			{
				posint.y--;
				m_MoveFlag = true;
			}
			if (IsKeyPress('S') && IsKeyPress('A'))
			{
				posint.y++;
				m_MoveFlag = true;
			}
			if (IsKeyPress('S') && IsKeyPress('D'))
			{
				posint.x--;
				m_MoveFlag = true;
			}

			if (posint.x > 5)
			{
				posint.x = 5;
			}
			else if (posint.x < 0)
			{
				posint.x = 0;
			}
			if (posint.y > 5)
			{
				posint.y = 5;
			}
			else if (posint.y < 0)
			{
				posint.y = 0;
			}

			if (m_PosInt.x != posint.x || m_PosInt.y != posint.y)
			{//À•W‚ª•Ï‚í‚Á‚Ä‚¢‚é
				switch (m_Route.size())
				{
				case 0:
					SceneGame::ChangeMoveNum(-1);
					m_Route.push_back(m_PosInt);
					break;
				default:
					DirectX::XMINT2 route = m_Route.back();
					if (route.x == posint.x && route.y == posint.y)
					{//’¼‘O‚É’Ê‚Á‚½êŠ‚Æ“¯‚¶“¹
						SceneGame::ChangeMoveNum(1);
						m_Route.pop_back();
					}
					else
					{
						SceneGame::ChangeMoveNum(-1);
						m_Route.push_back(m_PosInt);
					}
					break;
				}

				m_PosInt = posint;
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
	else
	{

	}
}

void Player::SetPosition(DirectX::XMINT2 num)
{
	m_PosInt = num;
	Stage* stage = SceneGame::GetObj<Stage>("Stage");
	m_Pos = stage->GetPosition(m_PosInt);
	m_Pos.y = 0.5f;
}

void Player::Reset()
{
	m_MoveFlag = false;
	m_Route.clear();
}
