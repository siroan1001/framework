#include "ModelManager.h"

std::shared_ptr<Model> ModelManager::m_pModelList[E_MODEL_KIND_MAX];

ModelManager& ModelManager::GetInstance()
{
	static ModelManager instance;
	return instance;
}

std::shared_ptr<Model> ModelManager::GetModel(ModelKind kind)
{
	return m_pModelList[kind];
}

ModelManager::ModelManager()
{
	for (int i = 0; i < ModelKind::E_MODEL_KIND_MAX; i++)
	{
		m_pModelList[i] = std::make_shared<Model>();
	}

	m_pModelList[ModelKind::E_MODEL_KIND_PLAYER]->Load("Assets/Model/player/player.fbx", 0.35f);
	m_pModelList[ModelKind::E_MODEL_KIND_PLAYER_RED]->Load("Assets/Model/player/P1/Player1.fbx", 0.35f);
	m_pModelList[ModelKind::E_MODEL_KIND_PLAYER_BLUE]->Load("Assets/Model/player/P2/player2.fbx", 0.35f);
	m_pModelList[ModelKind::E_MODEL_KIND_STAGE_LV0]->Load("Assets/Model/Stage3.0/Lv0/StageLv0.fbx");
	m_pModelList[ModelKind::E_MODEL_KIND_STAGE_RED_LV1]->Load("Assets/Model/Stage3.0/Red/Lv1/StageRedLv1.fbx");
	m_pModelList[ModelKind::E_MODEL_KIND_STAGE_RED_LV2]->Load("Assets/Model/Stage3.0/Red/Lv2/StageRedLv2.fbx");
	m_pModelList[ModelKind::E_MODEL_KIND_STAGE_RED_LV3]->Load("Assets/Model/Stage3.0/Red/Lv3/StageRedLv3.fbx");
	m_pModelList[ModelKind::E_MODEL_KIND_STAGE_BLUE_LV1]->Load("Assets/Model/Stage3.0/Blue/Lv1/StageBlueLv1.fbx");
	m_pModelList[ModelKind::E_MODEL_KIND_STAGE_BLUE_LV2]->Load("Assets/Model/Stage3.0/Blue/Lv2/StageBlueLv2.fbx");
	m_pModelList[ModelKind::E_MODEL_KIND_STAGE_BLUE_LV3]->Load("Assets/Model/Stage3.0/Blue/Lv3/StageBlueLv3.fbx");
	m_pModelList[ModelKind::E_MODEL_KIND_DICE]->Load("Assets/Model/dice2.0/dice.fbx");
}

ModelManager::~ModelManager()
{
}
