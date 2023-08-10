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

	MenuUI* menu = CreateObj<MenuUI>("MenuUI", eObjectTag::E_OBJ_TAG_SPRITE);
	menu->SetPos(DirectX::XMFLOAT2(100.0f, 100.0f));
	//menu->SetSize(DirectX::XMFLOAT2(20.0f, 20.0f));
	menu->SetActive(true);

	RenderTarget* pWipeRTV = CreateObj<RenderTarget>("UIRTV", eObjectTag::E_OBJ_TAG_RTV);
	pWipeRTV->Create(DXGI_FORMAT_R8G8B8A8_UNORM, SCREEN_WIDTH, SCREEN_HEIGHT);
	DepthStencil* pWipeDSV = CreateObj<DepthStencil>("UIDSV", eObjectTag::E_OBJ_TAG_DSV);
	pWipeDSV->Create(SCREEN_WIDTH, SCREEN_HEIGHT, false);
}
void SceneGame::Uninit()
{
}
void SceneGame::Update(float tick)
{
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

void SceneGame::ChangeAction(Action action)
{
	m_Action = action;
}

void SceneGame::ActionMenu()
{


	//if (IsKeyRepeat('W'))
	//{//カーソル上

	//}

	//if (IsKeyRepeat('S'))
	//{//カーソル下

	//}

	//if (IsKeyTrigger('L'))
	//{//決定

	//}
}

void SceneGame::ActionRoll()
{
}

void SceneGame::ActionMove()
{
}