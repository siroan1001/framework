#include "TurnUI.h"
#include "GameUI.h"
#include "TextUI.h"

TurnUI::TurnUI()
{
	GameUI* bg = CreateUI<GameUI>("BG");
	bg->SetSize(DirectX::XMFLOAT2(200.0f, 100.0f));
	TextUI* text = CreateUI<TextUI>("Turn");
	text->SetCharSize(DirectX::XMFLOAT2(30.0f, 30.0f));
	text->SetString(L"あと９ターン");
	text->SetPos(DirectX::XMFLOAT2(-75.0f, 0.0f));
}

void TurnUI::SetTurnString(int num)
{
	std::wstring result;
	std::wstring NumStr = TextUI::intToFullWidthString(num);

	result = L"あと" + NumStr + L"ターン";

	GetUI<TextUI>("Turn")->SetString(result);
}
