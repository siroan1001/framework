#include "TitleUI.h"
#include "GameUI.h"
#include "SceneGame.h"
#include "CursorUI.h"
#include "Input.h"

TitleUI::TitleUI()
{
	m_State = TitleState::E_TITLE_STATE_START;
	GameUI* TitleBG = CreateUI<GameUI>("TitleBG");
	TitleBG->CreateTex("Assets/Texture/title1.png");
	TitleBG->SetSize(DirectX::XMFLOAT2(1280.0f, 720.0f));
	CursorUI* Cursor = CreateUI<CursorUI>("Cursor");
	Cursor->SetSize(DirectX::XMFLOAT2(50.0f, 50.0f));
	Cursor->SetPos(DirectX::XMFLOAT2(-170.0f, 30.0f));
	m_ChoicePos[0] = DirectX::XMFLOAT2(640.0f + -170.0f, 360.0f + 30.0f);
	m_ChoicePos[1] = DirectX::XMFLOAT2(640.0f + -170.0f, 360.0f + 145.0f);
	m_ChoicePos[2] = DirectX::XMFLOAT2(640.0f + -170.0f, 360.0f + 260.0f);
}

void TitleUI::Update()
{
	GetUI<CursorUI>("Cursor")->Update();
	TitleState state = m_State;
	if (IsKeyTrigger('W'))
	{
		state = static_cast<TitleState>(m_State - 1);
		if (state <= -1)
			state = TitleState::E_TITLE_STATE_END;
	}
	if (IsKeyTrigger('S'))
	{
		state = static_cast<TitleState>(m_State + 1);
		if (state >= TitleState::E_TITLE_STATE_MAX)
			state = TitleState::E_TITLE_STATE_START;
	}
	if (IsKeyTrigger('L'))
	{

	}
	if (m_State != state)
	{
		m_State = state;
		GetUI<CursorUI>("Cursor")->SetPos(m_ChoicePos[m_State]);
	}
}

void TitleUI::Draw()
{
	GetUI<GameUI>("TitleBG")->Draw();
	GetUI<CursorUI>("Cursor")->Draw();
}
