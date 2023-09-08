#include "MenuUI.h"
#include "ShaderManager.h"
#include "Input.h"
#include "SceneGame.h"
#include "SceneRoot.h"

MenuUI::MenuUI()
{
	m_ChoiceNum = 2;
	GameUI* BG = CreateUI<GameUI>("BG");
	BG->CreateTex("Assets/Texture/MenuBG.png");
	BG->SetSize(DirectX::XMFLOAT2(275.0f, 75.0f));
	CursorUI* Cursor = CreateUI<CursorUI>("Cursor");
	Cursor->SetPos(DirectX::XMFLOAT2(-105.0f, 0.0f));
	TextUI* choice = CreateUI<TextUI>("choice1");
	choice->SetString(L"サイコロをふる");
	choice->SetCharSize(DirectX::XMFLOAT2(30.0f, 30.0f));
	choice->SetPos(DirectX::XMFLOAT2(-65.0f, 0.0f));

	m_Use = false;
	m_Kind = E_MENU_KIND_DICE;
}

void MenuUI::Update()
{
	if (!m_Use)	return;

	GetUI<CursorUI>("Cursor")->Update();

	if (IsKeyTrigger('L'))
	{//決定
		if(m_Kind == E_MENU_KIND_DICE)	
			SceneRoot::PlayMusic("Assets/Music/SE/決定ボタンを押す1.wav", false);
			SceneGame::SetNextAction(SceneGame::Action::E_ACTION_ROLL);
	}
}
