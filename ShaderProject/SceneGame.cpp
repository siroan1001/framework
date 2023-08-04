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

void SceneGame::Init()
{
	Player* modelA = CreateObj<Player>("ModelA", eObjectTag::E_OBJ_TAG_OBJ);

	Stage* stage = CreateObj<Stage>("Stage", eObjectTag::E_OBJ_TAG_OBJ);
	
	m_CamType = eCamType::E_CAM_TYPE_GAME_MAIN;
}
void SceneGame::Uninit()
{
}
void SceneGame::Update(float tick)
{
}

void SceneGame::Draw()
{
	std::list<ObjectBase*> objlist = GetObjswithTag<ObjectBase>(eObjectTag::E_OBJ_TAG_OBJ);

	for (ObjectBase* obj : objlist)
	{
		obj->Draw();
	}
}