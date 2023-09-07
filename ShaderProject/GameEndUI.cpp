#include "GameEndUI.h"
#include "GameUI.h"
#include "TextUI.h"

GameEndUI::GameEndUI()
{
	GameUI* BG = CreateUI<GameUI>("BG");
	BG->CreateTex("Assets/Texture/PlayerUI.png");
	BG->SetSize(DirectX::XMFLOAT2(900.0f, 500.0f));
	m_Use = false;
}