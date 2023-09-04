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
			//ui->CreateTex("Assets/Texture/text.png");
			ui->SetTexture(m_pTex);
			m_CharUI.push_back(ui);
			diff++;
		}
		if (diff > 0)
		{
			m_CharUI.pop_back();
			diff--;
		}
	}

	bool flag;
	m_CharPair.clear();
	for(int num = 0; num < m_Str.size(); num++)
	{
		flag = false;
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (m_Str[num] == characters[i][j])
				{
					m_CharUI[num]->SetUVPos(DirectX::XMFLOAT2(m_uvSize.x * j, -m_uvSize.y + -m_uvSize.y * i));
					flag = true;
					break;
				}
			}
			if (flag)	break;
		}
	}
}

void TextUI::SetCharSize(DirectX::XMFLOAT2 size)
{
	m_CharSize = size; 
	for (int i = 0; i < m_CharUI.size(); i++)
	{
		m_CharUI[i]->SetSize(m_CharSize);
	}
	m_Size.y = m_CharSize.y;
}

void TextUI::SetPos(DirectX::XMFLOAT2 pos)
{
	for (GameUI* charUI : m_CharUI)
	{
		charUI->SetPos(pos);
		pos.x += m_CharSize.x;
	}
}

std::wstring TextUI::intToFullWidthString(int num, bool fill, int size)
{
	static const wchar_t fullWidthDigits[] = L"‚O‚P‚Q‚R‚S‚T‚U‚V‚W‚X";
	std::wstring result;

	while (num > 0) {
		int digit = num % 10;
		result = fullWidthDigits[digit] + result;
		num /= 10;
	}

	if (result.empty())	result = fullWidthDigits[0];

	if (fill && result.size() < size) {
		int zeroCount = size - result.size();
		std::wstring zeros(zeroCount, fullWidthDigits[0]);
		result = zeros + result;
	}

	return result;
}

