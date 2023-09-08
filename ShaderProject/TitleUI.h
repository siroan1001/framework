#pragma once
#include "UIBase.h"
class TitleUI : public UIBase
{
public:
	enum TitleState
	{
		E_TITLE_STATE_START = 0,
		E_TITLE_STATE_INFO,
		E_TITLE_STATE_END,
		E_TITLE_STATE_MAX,
	};

public:
	TitleUI();
	void Update();
	void Draw();

	TitleState GetTitleState() { return m_State; }

private:
	TitleState m_State;
	DirectX::XMFLOAT2 m_ChoicePos[3];
};

