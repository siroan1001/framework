#pragma once

#include "Model.h"

class ModelManager
{
public:
	enum ModelKind
	{
		E_MODEL_KIND_PLAYER = 0,
		E_MODEL_KIND_STAGE,
		E_MODEL_KIND_MAX,
	};

public:
	static ModelManager& GetInstance();

	static std::shared_ptr<Model> GetModel(ModelKind kind);

private:
	ModelManager();
	~ModelManager();

	static std::vector<std::shared_ptr<Model>> m_pModelList;
};

