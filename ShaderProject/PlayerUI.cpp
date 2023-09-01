#include "PlayerUI.h"

PlayerUI::PlayerUI()
{
	GameUI* BG = CreateUI<GameUI>("BG");
	BG->CreateTex("Assets/Texture/PlayerUI.png");
	BG->SetSize(DirectX::XMFLOAT2(240.0f, 80.0f));
	TextUI* Name = CreateUI<TextUI>("Name");
	Name->SetString(L"ƒvƒŒƒCƒ„[‚P");
	Name->SetPos(DirectX::XMFLOAT2(-90.0f, -10.0f));
	Name->SetCharSize(DirectX::XMFLOAT2(25.0f, 25.0f));
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::Update()
{
}

