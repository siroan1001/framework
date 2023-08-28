#pragma once

#include "Model.h"

class ModelManager
{
public:
	enum ModelKind
	{
		E_MODEL_KIND_PLAYER = 0,
		E_MODEL_KIND_STAGE_LV0,
		E_MODEL_KIND_STAGE_RED_LV1,
		E_MODEL_KIND_STAGE_RED_LV2,
		E_MODEL_KIND_STAGE_RED_LV3,
		E_MODEL_KIND_STAGE_BLUE_LV1,
		E_MODEL_KIND_STAGE_BLUE_LV2,
		E_MODEL_KIND_STAGE_BLUE_LV3,
		E_MODEL_KIND_DICE,
		E_MODEL_KIND_MAX,
	};

public:
	static ModelManager& GetInstance();

	static std::shared_ptr<Model> GetModel(ModelKind kind);

private:
	ModelManager();
	~ModelManager();

	static std::shared_ptr<Model> m_pModelList[E_MODEL_KIND_MAX];
};

