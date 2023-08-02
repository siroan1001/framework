#include "Player.h"

Player::Player()
{
	m_pModel = std::make_shared<Model>();
	m_pModel->Load("Assets/Model/spot/spot.fbx");
}

Player::~Player()
{
}
