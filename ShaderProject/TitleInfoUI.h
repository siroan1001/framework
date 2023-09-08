#pragma once
#include "UIBase.h"
#include "Texture.h"

class TitleInfoUI : public UIBase
{
public:
	TitleInfoUI();
	void Update();
	void NextPage(int num);
	void ResetPage();

private:
	const char* m_pTexList[4];
	int m_CurentNum;
};

