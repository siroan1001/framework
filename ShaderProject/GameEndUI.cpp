#include "GameEndUI.h"
#include "GameUI.h"
#include "TextUI.h"
#include "CursorUI.h"

GameEndUI::GameEndUI()
{
	GameUI* sp = CreateUI<GameUI>("BG");
	sp->SetSize(DirectX::XMFLOAT2(900.0f, 500.0f));
	sp->SetColor(DirectX::XMFLOAT4(0.2f, 0.2f, 0.2f, 0.8f));

	sp = CreateUI<GameUI>("WL");
	sp->CreateTex("Assets/Texture/PlayerUI.png");
	sp->SetPos(DirectX::XMFLOAT2(0.0f, -50.0f));
	sp->SetSize(DirectX::XMFLOAT2(440.0f, 284.0f));

	sp = CreateUI<GameUI>("Info");
	sp->CreateTex("Assets/Texture/ResultInfo.png");
	sp->SetPos(DirectX::XMFLOAT2(0.0f, 150.0f));
	sp->SetSize(DirectX::XMFLOAT2(377.0f, 67.0f));

	
	m_Use = false;
}

void GameEndUI::SetWLSprite(bool flag)
{
	GameUI* sp = GetUI<GameUI>("WL");

	if (flag)
	{
		sp->CreateTex("Assets/Texture/win.png");
	}
	else
	{
		sp->CreateTex("Assets/Texture/lose.png");
	}
}
