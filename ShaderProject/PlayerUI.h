#pragma once
#include "GameUI.h"
#include "TextUI.h"
#include "UIBase.h"
#include "Player.h"

class PlayerUI : public UIBase
{
public:
	PlayerUI();
	~PlayerUI();
	void Update();

	void SetBGSprite(Player::PlayerNum pnum);
	void SetNameString(const wchar_t* str);
	void SetMoneyString(int num);

public:
	//GameUI* m_pBG;
	//TextUI* m_pName;
	//TextUI* m_pMoney;
	//TextUI* m_pChangeMoney;
};

