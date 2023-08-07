#include "ModelManager.h"

std::vector<std::shared_ptr<Model>> ModelManager::m_pModelList;

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
	std::shared_ptr<Model> model;
	model = std::make_shared<Model>();
	model->Load("Assets/Model/player/player.fbx", 0.35f);
	m_pModelList.push_back(model);
	model = std::make_shared<Model>();;
	model->Load("Assets/Model/stage/stage.fbx");
	m_pModelList.push_back(model);
}

ModelManager::~ModelManager()
{
}
