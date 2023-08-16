#include "SceneGame.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "Input.h"
#include "Defines.h"
#include "Timer.h"

#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "CameraGameMain.h"
#include "CameraDebug.h"
#include "GameUI.h"
#include "MenuUI.h"
#include "Dice.h"


#include <string>

SceneGame::Action SceneGame::m_Action;
SceneGame::Action SceneGame::m_NextAction;
int SceneGame::m_MoveNum;

void SceneGame::Init()
{
	m_pStage = CreateObj<Stage>("Stage", eObjectTag::E_OBJ_TAG_OBJ);

	m_pPlayer[E_PLAYER_NUM_1] = CreateObj<Player>(m_Name[PlayerNum::E_PLAYER_NUM_1], eObjectTag::E_OBJ_TAG_OBJ);
	m_pPlayer[E_PLAYER_NUM_1]->SetRotation(DirectX::XMFLOAT3(0.0f, 180.0f, 0.0f));
	m_pPlayer[E_PLAYER_NUM_1]->SetPosition(DirectX::XMINT2(5, 5));
	m_pPlayer[E_PLAYER_NUM_2] = CreateObj<Player>(m_Name[PlayerNum::E_PLAYER_NUM_2], eObjectTag::E_OBJ_TAG_OBJ);
	m_pPlayer[E_PLAYER_NUM_2]->SetRotation(DirectX::XMFLOAT3(0.0f, -90.0f, 0.0f));
	m_pPlayer[E_PLAYER_NUM_2]->SetPosition(DirectX::XMINT2(0, 0));
	m_pPlayer[E_PLAYER_NUM_2]->SetAIFlag(true);

	m_CamType = eCamType::E_CAM_TYPE_GAME_MAIN;

	m_PlayerTurn = SceneGame::PlayerNum::E_PLAYER_NUM_1;
	m_Action = Action::E_ACTION_MENU;
	m_NextAction = m_Action;
	m_MoveNum = 0;

	m_pMenuUI = CreateObj<MenuUI>("MenuUI", eObjectTag::E_OBJ_TAG_SPRITE);
	m_pMenuUI->SetPos(DirectX::XMFLOAT2(150.0f, 150.0f));
	m_pMenuUI->SetActive(false);

	m_pDiceNumUI = CreateObj<TextUI>("DiceNumUI", eObjectTag::E_OBJ_TAG_SPRITE);
	m_pDiceNumUI->SetPos(DirectX::XMFLOAT2(600.0f, 680.0f));
	m_pDiceNumUI->SetActive(false);
	m_pDiceNumUI->SetCharSize(DirectX::XMFLOAT2(45.0f, 45.0f));
	m_pDiceNumUI->SetString(L"���ƂO");

	m_Dice = CreateObj<Dice>("Dice", eObjectTag::E_OBJ_TAG_OBJ);
	m_Dice->SetPosition(DirectX::XMFLOAT3(5.0f, 2.5f, -5.0f));
	m_Dice->SetActive(false);

	ChengeAction();
}
void SceneGame::Uninit()
{
}
void SceneGame::Update(float tick)
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

	for (GameUI* obj : UIlist)
	{
		obj->Draw();
	}

	m_pDiceNumUI->Draw();
}

void SceneGame::SetNextAction(Action action)
{
	m_NextAction = action;
}

void SceneGame::SetMoveNum(int num)
{
	m_MoveNum = num;
	Timer::StartTimer(1.0f);
}

void SceneGame::ActionMenu()
{
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
		break;
	default:
		break;
	}

	switch (m_NextAction)
	{
	case SceneGame::E_ACTION_MENU:
		GetObj<MenuUI>("MenuUI")->SetActive(true);
		break;
	case SceneGame::E_ACTION_ROLL:
		GetObj<Dice>("Dice")->SetActive(true);
		break;
	case SceneGame::E_ACTION_MOVE:
		GetObj<TextUI>("DiceNumUI")->SetActive(true);

		break;
	default:
		break;
	}

	m_Action = m_NextAction;
}
