#include "TurnUI.h"
#include "GameUI.h"
#include "TextUI.h"

TurnUI::TurnUI()
{
	GameUI* bg = CreateUI<GameUI>("BG");
	bg->SetSize(DirectX::XMFLOAT2(200.0f, 100.0f));
	TextUI* text = CreateUI<TextUI>("Turn");
	text->SetCharSize(DirectX::XMFLOAT2(30.0f, 30.0f));
	text->SetString(L"‚ ‚Æ‚Xƒ^[ƒ“");
	text->SetPos(DirectX::XMFLOAT2(-80.0f, 0.0f));
}