#pragma once

#include "GameUI.h"
#include "TextUI.h"
#include <vector>

class MenuUI : public GameUI
{
private:
	enum MenuKind
	{
		E_MENU_KIND_DICE = 0,
		E_MENU_KIND_ITEM,
		E_MENU_KIND_MAX,
	};

public:
	MenuUI();
	~MenuUI();
	void Update();
	void Draw();

	void SetPos(DirectX::XMFLOAT2 pos) final;

private:
	GameUI* m_pBG;
	GameUI* m_pCursor;
	std::vector <TextUI*> m_pChoice;
	int m_ChoiceNum;
	MenuKind m_Kind;
};

