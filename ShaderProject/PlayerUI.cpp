#include "PlayerUI.h"
#include <iostream>
#include <string>
#include <locale>
#include <sstream>

PlayerUI::PlayerUI()
{
	GameUI* BG = CreateUI<GameUI>("BG");
	BG->CreateTex("Assets/Texture/PlayerUI.png");
	BG->SetSize(DirectX::XMFLOAT2(240.0f, 80.0f));
	TextUI* Name = CreateUI<TextUI>("Name");
	Name->SetString(L"ƒvƒŒƒCƒ„[‚P");
	Name->SetPos(DirectX::XMFLOAT2(-90.0f, -10.0f));
	Name->SetCharSize(DirectX::XMFLOAT2(25.0f, 25.0f));
	TextUI* Money = CreateUI<TextUI>("Money");
	Money->SetString(L"‚O‚O‚O‚O");
	Money->SetPos(DirectX::XMFLOAT2(55.0f, 18.0f));
	Money->SetCharSize(DirectX::XMFLOAT2(15.0f, 15.0f));
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::Update()
{
}

void PlayerUI::SetNameString(const wchar_t * str)
{
	GetUI<TextUI>("Name")->SetString(str);
}

void PlayerUI::SetMoneyString(int num)
{
	std::wstring wstr = TextUI::intToFullWidthString(num, true, 4);

	GetUI<TextUI>("Money")->SetString(wstr);
}

