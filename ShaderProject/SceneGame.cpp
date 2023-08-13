#include "SceneGame.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "Input.h"
#include "Defines.h"

#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "CameraGameMain.h"
#include "CameraDebug.h"
#include "GameUI.h"
#include "MenuUI.h"
#include "Dice.h"

SceneGame::Action SceneGame::m_Action;
SceneGame::Action SceneGame::m_NextAction;

void SceneGame::Init()
{
	Player* player;
	player = CreateObj<Player>(m_Name[PlayerNum::E_PLAYER_NUM_1], eObjectTag::E_OBJ_TAG_OBJ);
	player->SetRotation(DirectX::XMFLOAT3(0.0f, 180.0f, 0.0f));
	player->SetPosition(DirectX::XMFLOAT3(5.0f, 0.5f, -5.0f));
	player = CreateObj<Player>(m_Name[PlayerNum::E_PLAYER_NUM_2], eObjectTag::E_OBJ_TAG_OBJ);
	player->SetRotation(DirectX::XMFLOAT3(0.0f, -90.0f, 0.0f));
	player->SetPosition(DirectX::XMFLOAT3(-5.0f, 0.5f, 5.0f));
	player->SetAIFlag(true);

	Stage* stage = CreateObj<Stage>("Stage", eObjectTag::E_OBJ_TAG_OBJ);

	m_CamType = eCamType::E_CAM_TYPE_GAME_MAIN;

	m_PlayerTurn = SceneGame::PlayerNum::E_PLAYER_NUM_1;
	m_Action = Action::E_ACTION_MENU;
	m_NextAction = m_Action;

	MenuUI* menu = CreateObj<MenuUI>("MenuUI", eObjectTag::E_OBJ_TAG_SPRITE);
	menu->SetPos(DirectX::XMFLOAT2(200.0f, 200.0f));
	menu->SetActive(false);

	Dice* dice = CreateObj<Dice>("Dice", eObjectTag::E_OBJ_TAG_OBJ);
	dice->SetPosition(DirectX::XMFLOAT3(5.0f, 2.5f, -5.0f));
	dice->SetActive(false);

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
}

void SceneGame::SetNextAction(Action action)
{
	m_NextAction = action;
}

void SceneGame::ActionMenu()
{
	GetObj<MenuUI>("MenuUI")->Update();
}

void SceneGame::ActionRoll()
{
	GetObj<Dice>("Dice")->Update();
}

void SceneGame::ActionMove()
{
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
		break;
	default:
		break;
	}

	m_Action = m_NextAction;
}
