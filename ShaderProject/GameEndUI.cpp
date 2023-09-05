#include "GameEndUI.h"
#include "GameUI.h"
#include "TextUI.h"

GameEndUI::GameEndUI()
{
	GameUI* BG = CreateUI<GameUI>("BG");
	BG->CreateTex("Assets/Texture/PlayerUI.png");
	BG->SetSize(DirectX::XMFLOAT2(400.0f, 300.0f));
	m_Use = false;
}