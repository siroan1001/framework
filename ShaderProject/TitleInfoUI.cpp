#include "TitleInfoUI.h"
#include "GameUI.h"
#include "Input.h"

TitleInfoUI::TitleInfoUI() : m_CurentNum(0)
{
	GameUI* bg = CreateUI<GameUI>("Info");

	m_pTexList[0] = "Assets/Texture/rule/スライド1.png";
	m_pTexList[1] = "Assets/Texture/rule/スライド2.png";
	m_pTexList[2] = "Assets/Texture/rule/スライド3.png";
	m_pTexList[3] = "Assets/Texture/rule/スライド4.png";
	bg->CreateTex(m_pTexList[0]);
	bg->SetSize(DirectX::XMFLOAT2(960.0f, 540.0f));
}

void TitleInfoUI::Update()
{
	if (!m_Use)	return;

	if (IsKeyTrigger('A'))
	{
		NextPage(-1);
	}
	if (IsKeyTrigger('D'))
	{
		NextPage(1);
	}
}

void TitleInfoUI::NextPage(int num)
{
	m_CurentNum += num;
	if (m_CurentNum < 0)
	{
		m_CurentNum = 0;
	}
	else if (m_CurentNum > 3)
	{
		m_CurentNum = 3;
	}
	GetUI<GameUI>("Info")->CreateTex(m_pTexList[m_CurentNum]);
}

void TitleInfoUI::ResetPage()
{
	m_CurentNum = 0;
	GetUI<GameUI>("Info")->CreateTex(m_pTexList[m_CurentNum]);
}
