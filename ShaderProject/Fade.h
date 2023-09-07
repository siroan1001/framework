#pragma once
#include "UIBase.h"
#include "GameUI.h"

class Fade : public UIBase
{
public:
	enum FadeState
	{
		FADE_STOP = 0,
		FADE_IN,
		FADE_OUT,
		FADE_END,
	};

public:
	Fade();
	void Update();

	void StartFade();
	void EndFade();

	FadeState GetFadeState();

private:
	FadeState m_State;
	float m_Alpha;
};

