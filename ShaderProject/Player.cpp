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
	if (g_PlayerNum >= Player::E_PLAYER_NUM_MAX)	g_PlayerNum = Player::E_PLAYER_NUM_1;
	m_PlayerNum = g_PlayerNum;
	g_PlayerNum = static_cast<Player::PlayerNum>(g_PlayerNum + 1);
	switch (m_PlayerNum)
	{
	case Player::E_PLAYER_NUM_1:
		m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_PLAYER_RED);
		break;
	case Player::E_PLAYER_NUM_2:
		m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_PLAYER_BLUE);
		break;
	default:
		break;
	}

	m_AnimeFlag = true;
	m_MaxSize = 0.9f;
	m_CurentSize = 0.0f;
}

Player::~Player()
{
}

void Player::Update()
{
	if (!m_AIFlag)
	{//プレイヤーの動き
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

			if (posint.x > 3)
			{
				posint.x = 3;
			}
			else if (posint.x < 0)
			{
				posint.x = 0;
			}
			if (posint.y > 3)
			{
				posint.y = 3;
			}
			else if (posint.y < 0)
			{
				posint.y = 0;
			}

			if (m_PosInt.x != posint.x || m_PosInt.y != posint.y)
			{//座標が変わっている
				switch (m_Route.size())
				{
				case 0:
					SceneGame::ChangeMoveNum(-1);
					m_Route.push_back(m_PosInt);
					break;
				default:
					DirectX::XMINT2 route = m_Route.back();
					if (route.x == posint.x && route.y == posint.y)
					{//直前に通った場所と同じ道
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
	}// !プレイヤーの動き
	else
	{//　CPUの動き
		if (!Timer::IsUsed())	Timer::StartTimer(0.5f);

		DirectX::XMINT2 posint = m_PosInt;

		if (Timer::IsTimeElapsed())
		{
			while (m_PosInt.x == posint.x && m_PosInt.y == posint.y)
			{
				//移動する方向を乱数で決める
				int num = rand() % 4;

				//乱数に応じて移動させる
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

				//上限を超えるときの補正
				if (posint.x > 3)
				{
					posint.x = 3;
				}
				else if (posint.x < 0)
				{
					posint.x = 0;
				}
				if (posint.y > 3)
				{
					posint.y = 3;
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
	
	float sizeY;
	if (m_AnimeFlag)
	{
		sizeY = GetOrizinScale().y;
		m_CurentSize += 0.1f / 15.0f;
		sizeY = (1.0f - m_CurentSize);
		if (sizeY <= 0.9f)
		{
			m_CurentSize = 0.1f;
			sizeY = 0.9f;
			m_AnimeFlag = false;
		}
		sizeY = (1.0f - m_CurentSize);
	}
	else
	{
		sizeY = GetScale().y;
		sizeY += 0.1f / 15.0f;
		if (sizeY >= 1.0f)
		{
			m_CurentSize = 0.0f;
			sizeY = 1.0f;
			m_AnimeFlag = true;
		}
	}
	SetScale(DirectX::XMFLOAT3(1.0f, sizeY, 1.0f));
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
	{//自分のステージだった場合（レベル上げ処理）
		if (Lv < 3)
		{
			stage->LevelUpStage();
		}
	}
	else if (targetPNum == PlayerNum::E_PLAYER_NUM_MAX)
	{//まだ誰も確保していないステージだった場合（獲得処理）
		if (m_Money - 300 >= 0)
		{
			stage->KeepStage(m_PlayerNum);
			m_HaveStageNum.push_back(m_PosInt);
			AddMoney(-300);
		}
		else
		{//お金が足らなかった

		}
	}
	else
	{//他の人のステージだった場合（ダメージ処理）
		Player* player = SceneGame::GetObj<Player>(SceneGame::m_Name[targetPNum]);
		switch (Lv)
		{
		case 1:
			AddMoney(-200);
			player->AddMoney(200);
			break;
		case 2:
			AddMoney(-300);
			player->AddMoney(300);
			break;
		case 3:
			AddMoney(-500);
			player->AddMoney(500);
			break;
		default:
			break;
		}
		if (m_Money < 0)
		{
			AddMoney(-(m_Money));
		}
	}
}

int Player::GetPoint()
{
	int result = 0;
	for (DirectX::XMINT2 num : m_HaveStageNum)
	{
		StageObject* stage = SceneGame::GetObj<Stage>("Stage")->GetStageObj(num);
		int Lv = stage->GetLavel();
		result += Lv;
	}
	result += m_Money / 500;

	return result;
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
