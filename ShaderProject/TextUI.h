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
	void SetPos(DirectX::XMFLOAT2 pos);

	DirectX::XMFLOAT2 GetPos() { return m_CharUI[0]->GetPos(); }

public:
	static std::wstring intToFullWidthString(int num, bool fill = false, int size = 0);

private:
	std::wstring m_Str;
	DirectX::XMFLOAT2 m_CharSize;
    const wchar_t characters[12][16] = {
        L"�P�Q�R�S�T�U�V�W�X�O����������",
        L"�������������������������Ă�",
        L"�Ȃɂʂ˂̂͂Ђӂւق܂݂ނ߂�",
        L"����u�v����������o�p",
        L"�������������������������Âł�",
        L"�΂тԂׂڂς҂Ղ؂ۂ�����`",
        L"�A�E�C�G�I�J�L�N�P�R�T�V�X�Z�\",
        L"�^�`�c�e�g�i�j�k�l�m�n�q�t�w�z",
        L"�}�~�������������I�H����������",
        L"�������[�E�K�M�O�Q�S�U�W�Y�[�]",
        L"�_�a�d�f�h�o�r�u�x�{�p�s�v�y�|",
        L"�b�������{�����i�j�����������@",
    };
    std::vector<DirectX::XMINT2> m_CharPair;
    std::vector<GameUI*> m_CharUI;
};

