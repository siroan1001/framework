#include "TextUI.h"

TextUI::TextUI() : m_CharSize{0.0f, 0.0f}
{
	m_pTex = new Texture;
	m_pTex->Create("Assets/Texture/text.png");
	m_CharSize = DirectX::XMFLOAT2(10.0f, 20.0f);
	m_uvSize = DirectX::XMFLOAT2(1.0f / 15.0f, -1.0f / 12.0f);
}

TextUI::~TextUI()
{
}

void TextUI::Draw()
{
	if (!m_Use)	return;

	for (int i = 0; i < m_CharUI.size(); i++)
	{
		m_CharUI[i]->Draw();
	}
}

void TextUI::SetString(std::wstring str)
{
	m_Str = str;
	m_Size.x = m_CharSize.x * m_Str.size();

	int diff = m_CharUI.size() - m_Str.size();
	while (diff != 0)
	{
		if (diff < 0)
		{
			GameUI* ui = new GameUI;
			ui->SetSize(m_CharSize);
			ui->SetPos(DirectX::XMFLOAT2(m_Pos.x + m_CharSize.x * m_CharUI.size(), m_Pos.y));
			ui->SetUVSize(m_uvSize);
			ui->CreateTex("Assets/Texture/text.png");
			m_CharUI.push_back(ui);
			diff++;
		}
		if (diff > 0)
		{
			delete m_CharUI.back();
			diff--;
		}
	}

	m_CharPair.clear();
	for(int num = 0; num < m_Str.size(); num++)
	{
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (m_Str[num] == characters[i][j])
				{
					m_CharUI[num]->SetUVPos(DirectX::XMFLOAT2(m_uvSize.x * j, -m_uvSize.y + -m_uvSize.y * i));
					break;
				}
			}
		}
	}
}

void TextUI::SetCharSize(DirectX::XMFLOAT2 size)
{
	m_CharSize = size; 
	m_Size.y = m_CharSize.y;
}

