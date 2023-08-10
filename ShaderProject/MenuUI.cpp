#include "MenuUI.h"
#include "ShaderManager.h"
#include "Input.h"
#include "SceneGame.h"

MenuUI::MenuUI()
{
	m_ChoiceNum = 2;
	m_pBG = new GameUI();
	m_pBG->SetSize(DirectX::XMFLOAT2(150.0f, 75.0f * m_ChoiceNum));
	m_pBG->SetPS(ShaderManager::GetPSShader(ShaderManager::PSKind::E_PS_FRAME));
	m_pCursor = new GameUI();
	GameUI* choice = new GameUI();
	m_Use = false;
}

MenuUI::~MenuUI()
{
}

void MenuUI::Update()
{
	if (IsKeyRepeat('W'))
	{//カーソル上
	
	}
	
	if (IsKeyRepeat('S'))
	{//カーソル下
	
	}
	
	if (IsKeyTrigger('L'))
	{//決定
		SceneGame::ChangeAction(SceneGame::Action::E_ACTION_ROLL);
	}
}

void MenuUI::Draw()
{
	if (!m_Use)	return;
	m_pBG->Draw();
}

void MenuUI::SetPos(DirectX::XMFLOAT2 pos)
{
	m_Pos = pos;
	m_pBG->SetPos(pos);
}
