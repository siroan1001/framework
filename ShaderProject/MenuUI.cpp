#include "MenuUI.h"
#include "ShaderManager.h"
#include "Input.h"
#include "SceneGame.h"

MenuUI::MenuUI()
{
	m_ChoiceNum = 2;
	GameUI* BG = CreateUI<GameUI>("BG");
	BG->CreateTex("Assets/Texture/MenuBG.png");
	BG->SetSize(DirectX::XMFLOAT2(275.0f, 75.0f));
	GameUI* Cursor = CreateUI<GameUI>("Cursor");
	Cursor->CreateTex("Assets/Texture/yazirusi.png");
	Cursor->SetSize(DirectX::XMFLOAT2(25.0f, 25.0f));
	Cursor->SetPos(DirectX::XMFLOAT2(-105.0f, 0.0f));
	TextUI* choice = CreateUI<TextUI>("choice1");
	choice->SetString(L"ƒTƒCƒRƒ‚ð‚Ó‚é");
	choice->SetCharSize(DirectX::XMFLOAT2(30.0f, 30.0f));
	choice->SetPos(DirectX::XMFLOAT2(-65.0f, 0.0f));

	m_Use = false;
	m_Kind = E_MENU_KIND_DICE;
	m_maxMove = -15.0f;
	m_CurentMove = 0.0f;
	m_MoveFlag = true;
}

void MenuUI::Update()
{
	if (!m_Use)	return;

	GameUI* Cursor = GetUI<GameUI>("Cursor");

	if (m_MoveFlag)
	{
		m_CurentMove += m_maxMove / 10.0f;
		if (m_CurentMove <= m_maxMove)
		{
			m_CurentMove = m_maxMove;
			m_MoveFlag = false;
		}
	}
	else
	{
		m_CurentMove -= m_maxMove / 10.0f;
		if (m_CurentMove >= 0.0f)
		{
			m_CurentMove = 0.0f;
			m_MoveFlag = true;
		}
	}		
	DirectX::XMFLOAT2 pos;
	pos.x = GetPos().x - 105.0f - m_CurentMove;
	pos.y = GetPos().y;
	Cursor->SetPos(pos);

	if (IsKeyTrigger('L'))
	{//Œˆ’è
		if(m_Kind == E_MENU_KIND_DICE)	
			SceneGame::SetNextAction(SceneGame::Action::E_ACTION_ROLL);
	}
}
