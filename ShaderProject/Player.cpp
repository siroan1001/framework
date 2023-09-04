#include "Player.h"
#include "ModelManager.h"
#include "SceneGame.h"
#include "Stage.h"
#include "StageObject.h"
#include "Input.h"
#include "Timer.h"

static Player::PlayerNum g_PlayerNum = Player::PlayerNum::E_PLAYER_NUM_1;

Player::Player() : m_AIFlag(false), m_MoveFlag(false), m_LastMove(999), m_Money(500)
{
	m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_PLAYER);
	m_PlayerNum = g_PlayerNum;
	g_PlayerNum = static_cast<Player::PlayerNum>(g_PlayerNum + 1);
}

Player::~Player()
{
}

void Player::Update()
{
	if (!m_AIFlag)
	{//�v���C���[�̓���
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
			{//���W���ς���Ă���
				switch (m_Route.size())
				{
				case 0:
					SceneGame::ChangeMoveNum(-1);
					m_Route.push_back(m_PosInt);
					break;
				default:
					DirectX::XMINT2 route = m_Route.back();
					if (route.x == posint.x && route.y == posint.y)
					{//���O�ɒʂ����ꏊ�Ɠ�����
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
	}// !�v���C���[�̓���
	else
	{//�@CPU�̓���
		if (!Timer::IsUsed())	Timer::StartTimer(0.5f);

		DirectX::XMINT2 posint = m_PosInt;

		if (Timer::IsTimeElapsed())
		{
			while (m_PosInt.x == posint.x && m_PosInt.y == posint.y)
			{
				//�ړ���������𗐐��Ō��߂�
				int num = rand() % 4;

				//�����ɉ����Ĉړ�������
				switch (num)
				{
				case 0:
					if (m_LastMove == 1)	continue;
					posint.x++;
					break;
				case 1:
					if (m_LastMove == 0)	continue;
					posint.x--;
					break;
				case 2:
					if (m_LastMove == 3)	continue;
					posint.y++;
					break;
				case 3:
					if (m_LastMove == 2)	continue;
					posint.y--;
					break;
				}

				//����𒴂���Ƃ��̕␳
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
			}

			m_PosInt = posint;

			SetPosition(m_PosInt);
			SceneGame::ChangeMoveNum(-1);
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

void Player::StopedPlayer()
{
	StageObject* stage = SceneGame::GetObj<Stage>("Stage")->GetStageObj(m_PosInt);
	Player::PlayerNum targetPNum = stage->GetHuvingPlayer();
	int Lv = stage->GetLavel();
	if (targetPNum == m_PlayerNum)
	{//�����̃X�e�[�W�������ꍇ�i���x���グ�����j
		if (Lv > 3)
		{
			stage->LevelUpStage();
		}
	}
	else if (targetPNum == PlayerNum::E_PLAYER_NUM_MAX)
	{//�܂��N���m�ۂ��Ă��Ȃ��X�e�[�W�������ꍇ�i�l�������j
		if (m_Money - 300 >= 0)
		{
			stage->KeepStage(m_PlayerNum);
			AddMoney(-300);
		}
		else
		{//����������Ȃ�����

		}
	}
	else
	{//���̐l�̃X�e�[�W�������ꍇ�i�_���[�W�����j

	}
}

void Player::Reset()
{
	m_MoveFlag = false;
	m_Route.clear();
	m_LastMove = 999;
}

void Player::AddMoney(int num)
{
	m_Money += num;
	switch (m_PlayerNum)
	{
	case Player::E_PLAYER_NUM_1:
		SceneGame::GetObj<PlayerUI>("Player1UI")->SetMoneyString(m_Money);
		break;
	case Player::E_PLAYER_NUM_2:
		SceneGame::GetObj<PlayerUI>("Player2UI")->SetMoneyString(m_Money);
		break;
	default:
		break;
	}
}
