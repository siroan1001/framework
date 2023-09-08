#include "TitleInfoUI.h"
#include "GameUI.h"
#include "Input.h"
#include "CursorUI.h"
#include "SceneRoot.h"

TitleInfoUI::TitleInfoUI() : m_CurentNum(0)
{


	GameUI* bg = CreateUI<GameUI>("Info");

	m_pTexList[0] = "Assets/Texture/rule/スライド1.png";
	m_pTexList[1] = "Assets/Texture/rule/スライド2.png";
	m_pTexList[2] = "Assets/Texture/rule/スライド3.png";
	m_pTexList[3] = "Assets/Texture/rule/スライド4.png";
	bg->CreateTex(m_pTexList[0]);
	bg->SetSize(DirectX::XMFLOAT2(960.0f, 540.0f));

	CursorUI* Cursor = CreateUI<CursorUI>("Cursor1");
	Cursor->SetPos(DirectX::XMFLOAT2(500.0f, 0.0f));
	Cursor->SetAnimeFrame(25.0f);
	Cursor->SetMoveMax(2.0f);
	Cursor = CreateUI<CursorUI>("Cursor2");
	Cursor->SetPos(DirectX::XMFLOAT2(-500.0f, 0.0f));
	Cursor->SetAnimeFrame(25.0f);
	Cursor->SetMoveMax(2.0f);
	Cursor->SetRot(180.0f);
	Cursor->SetActive(false);
}

void TitleInfoUI::Update()
{
	if (!m_Use)	return;

	GetUI<CursorUI>("Cursor1")->Update();
	GetUI<CursorUI>("Cursor2")->Update();

	if (IsKeyTrigger('A'))
	{
		NextPage(-1);
	}
	if (IsKeyTrigger('D'))
	{
		NextPage(1);
	}

	CursorUI* cursor1 = GetUI<CursorUI>("Cursor1");
	CursorUI* cursor2 = GetUI<CursorUI>("Cursor2");
	if (m_CurentNum == 0)
	{
		cursor1->SetActive(true);
		cursor2->SetActive(false);
	}
	else if (m_CurentNum == 3)
	{
		cursor1->SetActive(false);
		cursor2->SetActive(true);
	}
	else
	{
		cursor1->SetActive(true);
		cursor2->SetActive(true);
	}
}

void TitleInfoUI::NextPage(int num)
{
	int hoge = m_CurentNum;
	m_CurentNum += num;
	if (m_CurentNum < 0)
	{
		m_CurentNum = 0;
	}
	else if (m_CurentNum > 3)
	{
		m_CurentNum = 3;
	}
	if (hoge != m_CurentNum)
	{
		SceneRoot::PlayMusic("Assets/Music/SE/se_08_page_para.wav", false);
		GetUI<GameUI>("Info")->CreateTex(m_pTexList[m_CurentNum]);
	}
	
}

void TitleInfoUI::ResetPage()
{
	m_CurentNum = 0;
	GetUI<GameUI>("Info")->CreateTex(m_pTexList[m_CurentNum]);
}
