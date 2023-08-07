#include "SceneGame.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "Input.h"

#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "CameraGameMain.h"
#include "CameraDebug.h"
#include "GameUI.h"

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

	CreateObj<GameUI>("SampleUI", eObjectTag::E_OBJ_TAG_SPRITE);
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

	GetObj<GameUI>("SampleUI")->Draw();


}

void SceneGame::ActionMenu()
{
	if (IsKeyRepeat('W'))
	{//カーソル上

	}

	if (IsKeyRepeat('S'))
	{//カーソル下

	}

	if (IsKeyTrigger('L'))
	{//決定

	}
}

void SceneGame::ActionRoll()
{
}

void SceneGame::ActionMove()
{
}
