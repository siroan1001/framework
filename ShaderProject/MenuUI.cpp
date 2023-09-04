#include "MenuUI.h"
#include "ShaderManager.h"
#include "Input.h"
#include "SceneGame.h"

MenuUI::MenuUI()
{
	m_ChoiceNum = 2;
	m_pBG = new GameUI();
	m_pBG->SetSize(DirectX::XMFLOAT2(150.0f, 75.0f));
	m_pBG->CreateTex("Assets/Texture/MenuBG.png");
	//m_pBG->SetPS(ShaderManager::GetPSShader(ShaderManager::PSKind::E_PS_FRAME));
	m_pCursor = new GameUI();
	TextUI* choice = new TextUI();
	choice->SetString(L"サイコロをふる");
	choice->SetCharSize(DirectX::XMFLOAT2(20.0f, 20.0f));
	choice->SetPos(DirectX::XMFLOAT2(-60.0f, 0.0f));
	m_pChoice.push_back(choice);
	choice = new TextUI();
	choice->SetString(L"アイテム");
	choice->SetCharSize(DirectX::XMFLOAT2(20.0f, 20.0f));
	choice->SetPos(DirectX::XMFLOAT2(30.0f, 0.0f));
	choice->SetActive(false);
	m_pChoice.push_back(choice);
	m_Use = false;
	m_Kind = E_MENU_KIND_DICE;
}

MenuUI::~MenuUI()
{
}

void MenuUI::Update()
{
	if (!m_Use)	return;

	if (IsKeyTrigger('W'))
	{//カーソル上
		m_pChoice[m_Kind]->SetActive(false);
		m_Kind = static_cast<MenuKind>(m_Kind - 1);
		if (m_Kind < 0)	m_Kind = E_MENU_KIND_ITEM;
		m_pChoice[m_Kind]->SetActive(true);
	}
	
	if (IsKeyTrigger('S'))
	{//カーソル下
		m_pChoice[m_Kind]->SetActive(false);
		m_Kind = static_cast<MenuKind>(m_Kind + 1);
		if (m_Kind == E_MENU_KIND_MAX)	m_Kind = E_MENU_KIND_DICE;
		m_pChoice[m_Kind]->SetActive(true);
	}

	if (IsKeyTrigger('L'))
	{//決定
		if(m_Kind == E_MENU_KIND_DICE)	
			SceneGame::SetNextAction(SceneGame::Action::E_ACTION_ROLL);
	}
}

void MenuUI::Draw()
{
	if (!m_Use)	return;
	m_pBG->Draw();
	for (TextUI* text : m_pChoice)
	{
		text->Draw();
	}
}

void MenuUI::SetPos(DirectX::XMFLOAT2 pos)
{
	m_Pos = pos;
	m_pBG->SetPos(pos);
	DirectX::XMFLOAT2 Curentpos;
	for (TextUI* text : m_pChoice)
	{
		Curentpos = text->GetPos();
		pos.x += Curentpos.x;
		pos.y += Curentpos.y;
		text->SetPos(pos);
	}
}
