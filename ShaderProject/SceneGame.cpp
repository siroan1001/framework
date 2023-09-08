#include "SceneGame.h"
#include "SceneRoot.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "Input.h"
#include "Defines.h"
#include "Timer.h"
#include "Fade.h"

#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "CameraGameMain.h"
#include "CameraDebug.h"
#include "GameUI.h"
#include "MenuUI.h"
#include "Dice.h"
#include "GameEndUI.h"

#include <string>

SceneGame::Action SceneGame::m_Action;
SceneGame::Action SceneGame::m_NextAction;
const char* SceneGame::m_Name[Player::PlayerNum::E_PLAYER_NUM_MAX];
Player::PlayerNum SceneGame::m_PlayerTurn;
int SceneGame::m_MoveNum;
int SceneGame::m_MoveNumMax;
bool SceneGame::m_PlayerChangeFlag;
int SceneGame::m_Turn;
bool SceneGame::m_End;

void SceneGame::Init()
{
	m_Name[Player::PlayerNum::E_PLAYER_NUM_1] = "Player1";
	m_Name[Player::PlayerNum::E_PLAYER_NUM_2] = "Player2";

	m_pStage = CreateObj<Stage>("Stage", eObjectTag::E_OBJ_TAG_OBJ);

	m_pPlayer[Player::PlayerNum::E_PLAYER_NUM_1] = CreateObj<Player>(m_Name[Player::PlayerNum::E_PLAYER_NUM_1], eObjectTag::E_OBJ_TAG_OBJ);
	m_pPlayer[Player::PlayerNum::E_PLAYER_NUM_1]->SetRotation(DirectX::XMFLOAT3(0.0f, 180.0f, 0.0f));
	m_pPlayer[Player::PlayerNum::E_PLAYER_NUM_1]->SetPosition(DirectX::XMINT2(3, 3));
	m_pPlayer[Player::PlayerNum::E_PLAYER_NUM_2] = CreateObj<Player>(m_Name[Player::PlayerNum::E_PLAYER_NUM_2], eObjectTag::E_OBJ_TAG_OBJ);
	m_pPlayer[Player::PlayerNum::E_PLAYER_NUM_2]->SetRotation(DirectX::XMFLOAT3(0.0f, -90.0f, 0.0f));
	m_pPlayer[Player::PlayerNum::E_PLAYER_NUM_2]->SetPosition(DirectX::XMINT2(0, 0));
	m_pPlayer[Player::PlayerNum::E_PLAYER_NUM_2]->SetAIFlag(true);

	m_CamType = eCamType::E_CAM_TYPE_GAME_MAIN;

	m_PlayerTurn = Player::PlayerNum::E_PLAYER_NUM_1;
	m_Action = Action::E_ACTION_MENU;
	m_NextAction = m_Action;
	m_MoveNum = 0;
	m_PlayerChangeFlag = false;
	m_Turn = 5;
	m_End = false;

	m_pMenuUI = CreateObj<MenuUI>("MenuUI", eObjectTag::E_OBJ_TAG_SPRITE);
	m_pMenuUI->SetPos(DirectX::XMFLOAT2(220.0f, 180.0f));
	m_pMenuUI->SetActive(false);

	m_pDiceNumUI = CreateObj<TextUI>("DiceNumUI", eObjectTag::E_OBJ_TAG_SPRITE);
	m_pDiceNumUI->SetActive(false);
	m_pDiceNumUI->SetCharSize(DirectX::XMFLOAT2(45.0f, 45.0f));
	m_pDiceNumUI->SetString(L"‚ ‚Æ‚O");
	m_pDiceNumUI->SetPos(DirectX::XMFLOAT2(600.0f, 690.0f));

	m_Dice = CreateObj<Dice>("Dice", eObjectTag::E_OBJ_TAG_OBJ);
	m_Dice->SetPosition(DirectX::XMFLOAT3(5.0f, 2.5f, -5.0f));
	m_Dice->SetActive(false);

	m_pBG = CreateObj<BG>("BG", eObjectTag::E_OBJ_TAG_SPRITE);
	m_pBG->SetPos(DirectX::XMFLOAT2(1280.0f / 2.0f, 720.0f / 2.0f));
	m_pBG->SetSize(DirectX::XMFLOAT2(1280.0f, 720.0f));
	m_pBG->CreateTex("Assets/Texture/BG.jpg");

	m_pPlayer1UI = CreateObj<PlayerUI>("Player1UI", eObjectTag::E_OBJ_TAG_SPRITE);
	m_pPlayer1UI->SetBGSprite(Player::PlayerNum::E_PLAYER_NUM_1);
	m_pPlayer1UI->SetPos(DirectX::XMFLOAT2(120.0f, 40.0f));
	m_pPlayer1UI->SetMoneyString(m_pPlayer[Player::PlayerNum::E_PLAYER_NUM_1]->GetMoney());

	m_pPlayer2UI = CreateObj<PlayerUI>("Player2UI", eObjectTag::E_OBJ_TAG_SPRITE);
	m_pPlayer2UI->SetBGSprite(Player::PlayerNum::E_PLAYER_NUM_2);
	m_pPlayer2UI->SetPos(DirectX::XMFLOAT2(1160.0f, 40.0f));
	m_pPlayer2UI->SetNameString(L"ƒvƒŒƒCƒ„[‚Q");
	m_pPlayer2UI->SetMoneyString(m_pPlayer[Player::PlayerNum::E_PLAYER_NUM_2]->GetMoney());

	m_pTurnUI = CreateObj<TurnUI>("TextUI", eObjectTag::E_OBJ_TAG_SPRITE);
	m_pTurnUI->SetPos(DirectX::XMFLOAT2(100.0f, 670.0f));
	m_pTurnUI->SetTurnString(m_Turn);

	m_pGameEndUI = CreateObj<GameEndUI>("GameEndUI", eObjectTag::E_OBJ_TAG_SPRITE);
	m_pGameEndUI->SetPos(DirectX::XMFLOAT2(640.0f, 360.0f));

	DirectX::XMFLOAT3 playerpos;
	m_pP1NameUI = CreateObj<Billboard>("P1NameUI", eObjectTag::E_OBJ_TAG_SPRITE);
	m_pP1NameUI->CreateTex("Assets/Texture/p1name.png");
	playerpos = m_pPlayer[Player::E_PLAYER_NUM_1]->GetPosition();
	playerpos.y += 1.25f;
	m_pP1NameUI->SetPos(playerpos);
	m_pP1NameUI->SetSize(DirectX::XMFLOAT2(1.0f, 0.27f));

	m_pP2NameUI = CreateObj<Billboard>("P2NameUI", eObjectTag::E_OBJ_TAG_SPRITE);
	m_pP2NameUI->CreateTex("Assets/Texture/p2name.png");
	playerpos = m_pPlayer[Player::E_PLAYER_NUM_2]->GetPosition();
	playerpos.y += 1.25f;
	m_pP2NameUI->SetPos(playerpos);
	m_pP2NameUI->SetSize(DirectX::XMFLOAT2(1.0f, 0.27f));

	ChengeAction();
}
void SceneGame::Uninit()
{
}
void SceneGame::Update(float tick)
{
	//if (IsKeyTrigger(VK_RETURN))
	//	SceneRoot::SetNextScene(SceneRoot::SceneKind::SCENE_TITLE);

	DirectX::XMFLOAT3 playerpos;
	playerpos = m_pPlayer[Player::E_PLAYER_NUM_1]->GetPosition();
	playerpos.y += 1.25f;
	m_pP1NameUI->SetPos(playerpos);
	playerpos = m_pPlayer[Player::E_PLAYER_NUM_2]->GetPosition();
	playerpos.y += 1.25f;
	m_pP2NameUI->SetPos(playerpos);

	if (m_End)
	{
		if (IsKeyPress('L'))
		{
			SceneRoot::SetNextScene(SceneRoot::SCENE_TITLE);
		}
		return;
	}

	if (m_PlayerChangeFlag)
	{
		PlayerChange();
		if(!m_End)	m_NextAction = E_ACTION_MENU;
		m_PlayerChangeFlag = false;
	}

	if (!m_End)
	{
		if (m_Action != m_NextAction)	ChengeAction();

		switch (m_Action)
		{
		case Action::E_ACTION_MENU:
			ActionMenu();
			break;
		case Action::E_ACTION_ROLL:
			ActionRoll();
			break;
		case Action::E_ACTION_MOVE:
			ActionMove();
			break;
		}
	}
	else
	{
		GameEnd();
	}
}

void SceneGame::Draw()
{
	std::list<ObjectBase*> objlist;
	objlist = GetObjswithTag<ObjectBase>(eObjectTag::E_OBJ_TAG_OBJ);

	for (ObjectBase* obj : objlist)
	{
		obj->Draw();
	}

	std::list<GameUI*> UIlist;
	UIlist = GetObjswithTag<GameUI>(eObjectTag::E_OBJ_TAG_SPRITE);

	m_pBG->Draw();
	m_pMenuUI->Draw();
	m_pDiceNumUI->Draw();
	m_pPlayer1UI->Draw();
	m_pPlayer2UI->Draw();
	m_pTurnUI->Draw();
	m_pGameEndUI->Draw();
	m_pP1NameUI->Draw();
	m_pP2NameUI->Draw();
}

void SceneGame::SetNextAction(Action action)
{
	m_NextAction = action;
}

void SceneGame::SetMoveNum(int num)
{
	m_MoveNum = num;
	m_MoveNumMax = m_MoveNum;
	GetObj<TextUI>("DiceNumUI")->SetPos(DirectX::XMFLOAT2(600.0f, 690.0f));
	Timer::StartTimer(1.0f);
}

void SceneGame::ChangeMoveNum(int num)
{
	m_MoveNum += num;
	std::wstring str = L"‚ ‚Æ" + TextUI::intToFullWidthString(m_MoveNum);
	GetObj<TextUI>("DiceNumUI")->SetString(str);
	GetObj<TextUI>("DiceNumUI")->SetPos(DirectX::XMFLOAT2(600.0f, 690.0f));
	if (m_MoveNum > m_MoveNumMax)	m_MoveNum = m_MoveNumMax;
}

void SceneGame::ActionMenu()
{
	if (GetObj<Player>(m_Name[m_PlayerTurn])->GetAIFlag())
	{
		m_NextAction = E_ACTION_ROLL;
		return;
	}
	GetObj<MenuUI>("MenuUI")->Update();
}

void SceneGame::ActionRoll()
{
	GetObj<Dice>("Dice")->Update();
	if (Timer::IsTimeElapsed())		
		m_NextAction = Action::E_ACTION_MOVE;
}

void SceneGame::ActionMove()
{
	GetObj<Player>(m_Name[m_PlayerTurn])->Update();
	if (m_MoveNum <= 0)
	{	
		GetObj<Player>(m_Name[m_PlayerTurn])->StopedPlayer();
		m_PlayerChangeFlag = true;
	}
}

void SceneGame::PlayerChange()
{
	m_MoveNum = 0;
	GetObj<Dice>("Dice")->Reset();
	GetObj<Player>(m_Name[m_PlayerTurn])->Reset();
	m_PlayerTurn = static_cast<Player::PlayerNum>(m_PlayerTurn + 1);
	if (m_PlayerTurn == Player::PlayerNum::E_PLAYER_NUM_MAX)
	{
		TurnChange();
		m_PlayerTurn = Player::PlayerNum::E_PLAYER_NUM_1;
	}
}

void SceneGame::TurnChange()
{
	m_Turn--;
	m_pTurnUI->SetTurnString(m_Turn);
	if (m_Turn <= 0)
	{
		m_End = true;
		return;
	}

	for (int i = 0; i < Player::PlayerNum::E_PLAYER_NUM_MAX; i++)
	{
		GetObj<Player>(m_Name[i])->AddMoney(400);
	}
}

void SceneGame::ChengeAction()
{
	switch (m_Action)
	{
	case SceneGame::E_ACTION_MENU:
		GetObj<MenuUI>("MenuUI")->SetActive(false);
		break;
	case SceneGame::E_ACTION_ROLL:
		GetObj<Dice>("Dice")->SetActive(false);
		break;
	case SceneGame::E_ACTION_MOVE:
		GetObj<TextUI>("DiceNumUI")->SetActive(false);
		break;
	default:
		break;
	}

	std::wstring str;

	switch (m_NextAction)
	{
	case SceneGame::E_ACTION_MENU:
		GetObj<MenuUI>("MenuUI")->SetActive(true);
		break;
	case SceneGame::E_ACTION_ROLL:
		GetObj<Dice>("Dice")->SetActive(true);
		DirectX::XMFLOAT3 pos = GetObj<Player>(m_Name[m_PlayerTurn])->GetPosition();
		pos.y = 2.5f;
		GetObj<Dice>("Dice")->SetPosition(pos);
		break;
	case SceneGame::E_ACTION_MOVE:
		str = L"‚ ‚Æ" + TextUI::intToFullWidthString(m_MoveNum);
		GetObj<TextUI>("DiceNumUI")->SetString(str);
		GetObj<TextUI>("DiceNumUI")->SetActive(true);
		break;
	default:
		break;
	}

	m_Action = m_NextAction;
}

void SceneGame::GameEnd()
{
	m_pGameEndUI->SetActive(true);
	int p1 = m_pPlayer[Player::E_PLAYER_NUM_1]->GetPoint();
	int p2 = m_pPlayer[Player::E_PLAYER_NUM_2]->GetPoint();
	if(p1 > p2)		m_pGameEndUI->SetWLSprite(true);
	else		m_pGameEndUI->SetWLSprite(false);
}
