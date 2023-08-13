#include "Dice.h"
#include "ModelManager.h"

Dice::Dice() : m_Num(0)
{
	m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_DICE);
}

Dice::~Dice()
{
}

void Dice::Update()
{
	if (!m_Use)	return;
	m_Rot.x += 5.0f;
	m_Rot.y -= 5.0f;

	m_Num = rand() % 6 + 1;
}
