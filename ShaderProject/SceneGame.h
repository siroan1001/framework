#pragma once
#include "SceneBase.hpp"
#include "Player.h"
#include "Stage.h"
#include "MenuUI.h"
#include "Dice.h"

class SceneGame : public SceneBase
{
public:
	enum PlayerNum
	{
		E_PLAYER_NUM_1 = 0,
		E_PLAYER_NUM_2,
		E_PLAYER_NUM_MAX,
	};

	enum Action
	{
		E_ACTION_MENU = 0,
		E_ACTION_ROLL,
		E_ACTION_MOVE,
		E_ACTION_MAX,
	};

public: 
	void Init();
	void Uninit();
	void Update(float tick);
	void Draw();

	static void SetNextAction(Action action);
	static void SetMoveNum(int num);

private:
	void ActionMenu();
	void ActionRoll();
	void ActionMove();

	void ChengeAction();

private:
	const char* m_Name[E_PLAYER_NUM_MAX] = { "Player1", "Player2" };
	PlayerNum m_PlayerTurn;
	static Action m_Action;
	static Action m_NextAction;
	static int m_MoveNum;

private:
	Player* m_pPlayer[E_PLAYER_NUM_MAX];
	Stage* m_pStage;
	MenuUI* m_pMenuUI;
	Dice* m_Dice;
};