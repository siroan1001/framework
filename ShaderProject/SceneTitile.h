#pragma once
#include "SceneBase.hpp"
#include "GameUI.h"
#include "TextUI.h"
#include "TitleInfoUI.h"
#include "TitleUI.h"

class SceneTitle : public SceneBase
{
public:
	void Init();
	void Uninit();
	void Update(float tick);
	void Draw();

private:
	static TitleUI* m_TitleBG;
	static TitleInfoUI* m_InfoUI;
	bool m_InfoFlag;
};

