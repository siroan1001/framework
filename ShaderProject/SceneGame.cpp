#include "SceneGame.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "Input.h"

#include "Player.h"
#include "Enemy.h"

void SceneGame::Init()
{
	Shader* shader[] = {
		CreateObj<VertexShader>("VS_Object", eObjectTag::E_OBJ_TAG_SHEDER),
		CreateObj<PixelShader>("PS_TexColor", eObjectTag::E_OBJ_TAG_SHEDER),
	};
	const char* file[] = {
		"Assets/Shader/VS_Object.cso",
		"Assets/Shader/PS_TexColor.cso",
	};

	int shaderNum = _countof(shader);
	for (int i = 0; i < shaderNum; ++i)
	{
		if (FAILED(shader[i]->Load(file[i])))
		{
			MessageBox(NULL, file[i], "Shader Error", MB_OK);
		}
	}

	Player* modelA = CreateObj<Player>("ModelA", eObjectTag::E_OBJ_TAG_OBJ);
	Player* modelB = CreateObj<Player>("ModelB", eObjectTag::E_OBJ_TAG_OBJ);
	Enemy*  modelC = CreateObj<Enemy> ("ModelC", eObjectTag::E_OBJ_TAG_OBJ);
	
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