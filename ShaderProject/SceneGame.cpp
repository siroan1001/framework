#include "SceneGame.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "Input.h"

#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "CameraGameMain.h"

void SceneGame::Init()
{
	//Player* modelA = CreateObj<Player>("ModelA", eObjectTag::E_OBJ_TAG_OBJ);
	//Player* modelB = CreateObj<Player>("ModelB", eObjectTag::E_OBJ_TAG_OBJ);
	//Enemy*  modelC = CreateObj<Enemy> ("ModelC", eObjectTag::E_OBJ_TAG_OBJ);

	Stage* stage = CreateObj<Stage>("Stage", eObjectTag::E_OBJ_TAG_OBJ);
	
	CameraBase* mainCam = CreateObj<CameraGameMain>("GameCam", eObjectTag::E_OBJ_TAG_CAM);
	mainCam->SetPos(DirectX::XMFLOAT3(0.0f, 3.5f, 7.5f));
	mainCam->SetLook(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	mainCam->SetUp(DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_useCam = mainCam;
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