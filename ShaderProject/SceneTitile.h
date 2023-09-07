#pragma once
#include "SceneBase.hpp"
#include "GameUI.h"
#include "TextUI.h"

class SceneTitle : public SceneBase
{
public:
	void Init();
	void Uninit();
	void Update(float tick);
	void Draw();

private:
	static GameUI* m_TitleBG;
};

