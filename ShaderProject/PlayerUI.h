#pragma once
#include "GameUI.h"
#include "TextUI.h"
#include "UIBase.h"

class PlayerUI : public UIBase
{
public:
	PlayerUI();
	~PlayerUI();
	void Update();

	void SetNameString(const wchar_t* str);

public:
	//GameUI* m_pBG;
	//TextUI* m_pName;
	//TextUI* m_pMoney;
	//TextUI* m_pChangeMoney;
};

