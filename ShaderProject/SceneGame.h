#pragma once
#include "SceneBase.hpp"

class SceneGame : public SceneBase
{
public: 
	void Init();
	void Uninit();
	void Update(float tick);
	void Draw();
};