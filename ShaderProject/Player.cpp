#include "Player.h"

Player::Player() : m_AIFlag(false)
{
	m_pModel = std::make_shared<Model>();
	m_pModel->Load("Assets/Model/spot/spot.fbx", 0.7f);
}

Player::~Player()
{
}
