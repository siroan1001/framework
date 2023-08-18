#pragma once
#include "SceneBase.hpp"
#include "Player.h"
#include "Stage.h"
#include "MenuUI.h"
#include "TextUI.h"
#include "Dice.h"
#include "BG.h"

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
	static void ChangeMoveNum(int num);

	static const char* GetPlayerName() { return m_Name[m_PlayerTurn]; }

private:
	void ActionMenu();
	void ActionRoll();
	void ActionMove();

	void TurnChange();

	void ChengeAction();

private:
	const static char* m_Name[E_PLAYER_NUM_MAX];
	static PlayerNum m_PlayerTurn;
	static Action m_Action;
	static Action m_NextAction;
	static int m_MoveNum;
	static int m_MoveNumMax;
	static bool m_TurnChangeFlag;

private:
	Player* m_pPlayer[E_PLAYER_NUM_MAX];
	Stage* m_pStage;
	MenuUI* m_pMenuUI;
	TextUI* m_pDiceNumUI;
	Dice* m_Dice;
	BG* m_pBG;
};