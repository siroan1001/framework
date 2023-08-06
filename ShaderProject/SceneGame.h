#pragma once
#include "SceneBase.hpp"
#include "Player.h"


class SceneGame : public SceneBase
{
public:
	enum PlayerNum
	{
		E_PLAYER_NUM_1 = 0,
		E_PLAYER_NUM_2,
		E_PLAYER_NUM_MAX,
	};

public: 
	void Init();
	void Uninit();
	void Update(float tick);
	void Draw();

private:
	Player* m_pPlayer[E_PLAYER_NUM_MAX];
};