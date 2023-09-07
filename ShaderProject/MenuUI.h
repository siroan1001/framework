#pragma once

#include "GameUI.h"
#include "TextUI.h"
#include "UIBase.h"
#include <vector>

class MenuUI : public UIBase
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
	void Update();

private:
	int m_ChoiceNum;
	MenuKind m_Kind;
	float m_maxMove;
	float m_CurentMove;
	bool m_MoveFlag;
};

