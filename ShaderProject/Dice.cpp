#include "Dice.h"
#include "ModelManager.h"

Dice::Dice()
{
	m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_DICE);
}

Dice::~Dice()
{
}

void Dice::Update()
{
}
