#pragma once
#include "SceneBase.hpp"
#include "Player.h"
//#include "Stage.h"
//#include "MenuUI.h"
//#include "TextUI.h"
//#include "Dice.h"
#include "BG.h"
#include "PlayerUI.h"
#include "TurnUI.h"
#include "Billboard.h"

class SceneGame : public SceneBase
{
public:
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

	void PlayerChange();
	void TurnChange();

	void ChengeAction();

	void GameEnd();

public:
	const static char* m_Name[Player::PlayerNum::E_PLAYER_NUM_MAX];

private:
	static Player::PlayerNum m_PlayerTurn;
	static Action m_Action;
	static Action m_NextAction;
	static int m_MoveNum;
	static int m_MoveNumMax;
	static bool m_PlayerChangeFlag;
	static int m_Turn;
	static bool m_End;
	static bool m_DiceRoll;

private:
	class Player* m_pPlayer[Player::PlayerNum::E_PLAYER_NUM_MAX];
	class Stage* m_pStage;
	class MenuUI* m_pMenuUI;
	class TextUI* m_pDiceNumUI;
	class Dice* m_Dice;
	class BG* m_pBG;
	class PlayerUI* m_pPlayer1UI;
	class PlayerUI* m_pPlayer2UI;
	class TurnUI* m_pTurnUI;
	class GameEndUI* m_pGameEndUI;
	class Billboard* m_pP1NameUI;
	class Billboard* m_pP2NameUI;
};