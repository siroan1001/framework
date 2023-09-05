#include "PlayerUI.h"
#include <iostream>
#include <string>
#include <locale>
#include <sstream>

PlayerUI::PlayerUI()
{
	GameUI* BG = CreateUI<GameUI>("BG");
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

void PlayerUI::SetBGSprite(Player::PlayerNum pnum)
{
	GameUI* BG = GetUI<GameUI>("BG");
	switch (pnum)
	{
	case Player::E_PLAYER_NUM_1:
		BG->CreateTex("Assets/Texture/Player1UI.png");
		break;
	case Player::E_PLAYER_NUM_2:
		BG->CreateTex("Assets/Texture/Player2UI.png");
		break;
	default:
		break;
	}
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

