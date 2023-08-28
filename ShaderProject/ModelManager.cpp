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
	for (std::shared_ptr<Model> model : m_pModelList)
	{
		model = std::make_shared<Model>();
	}
	m_pModelList[ModelKind::E_MODEL_KIND_PLAYER]->Load("Assets/Model/player/player.fbx", 0.35f);
	m_pModelList[ModelKind::E_MODEL_KIND_STAGE]->Load("Assets/Model/stage2.0/stage2.0.fbx");
	m_pModelList[ModelKind::E_MODEL_KIND_DICE]->Load("Assets/Model/dice/dice.fbx");
}

ModelManager::~ModelManager()
{
}
