#include "Player.h"
#include "ModelManager.h"

Player::Player() : m_AIFlag(false)
{
	m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_PLAYER);
	m_pModel->Load("Assets/Model/spot/spot.fbx", 0.7f);
}

Player::~Player()
{
}
