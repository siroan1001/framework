#include "Player.h"
#include "ModelManager.h"

Player::Player() : m_AIFlag(false)
{
	m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_PLAYER);
}

Player::~Player()
{
}

void Player::Update()
{
}
