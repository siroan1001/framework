#pragma once
#include "GameUI.h"
#include <string>
#include <vector>

class TextUI : public GameUI
{
public:
	TextUI();
	~TextUI();
    void Draw();

    void SetString(std::wstring str);
    void SetCharSize(DirectX::XMFLOAT2 size);

private:
	std::wstring m_Str;
	DirectX::XMFLOAT2 m_CharSize;
    const wchar_t characters[12][16] = {
        L"１２３４５６７８９０あういえお",
        L"かきくけこさしすせそたちつてと",
        L"なにぬねのはひふへほまみむめも",
        L"やゆよ「」らりるれろわをん｛｝",
        L"がぎぐげござじずぜぞだぢづでど",
        L"ばびぶべぼぱぴぷぺぽっゃゅょ～",
        L"アウイエオカキクケコサシスセソ",
        L"タチツテトナニヌネノハヒフヘホ",
        L"マミムメモヤユヨ！？ラリルレロ",
        L"ワヲンー・ガギグゲゴザジズゼゾ",
        L"ダヂヅデドバビブベボパピプペポ",
        L"ッャュョ＋＊＠（）＆＄％＃￥　",
    };
    std::vector<DirectX::XMINT2> m_CharPair;
    std::vector<GameUI*> m_CharUI;
};

