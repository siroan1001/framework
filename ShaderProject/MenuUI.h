#pragma once

#include "GameUI.h"
#include <vector>

class MenuUI : public GameUI
{
public:
	MenuUI();
	~MenuUI();
	void Update();
	void Draw();

	void SetActive(bool flag) { m_Use = flag; }
	void SetPos(DirectX::XMFLOAT2 pos) final;

private:
	GameUI* m_pBG;
	GameUI* m_pCursor;
	std::vector <GameUI*> m_pChoice;
	int m_ChoiceNum;
};

