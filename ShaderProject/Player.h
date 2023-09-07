#pragma once
#include "ObjectBase.h"
#include <vector>

class Player : public ObjectBase
{
public:
	enum PlayerNum
	{
		E_PLAYER_NUM_1 = 0,
		E_PLAYER_NUM_2,
		E_PLAYER_NUM_MAX,
	};

public:
	Player();
	~Player();
	void Update() final;

	void SetAIFlag(bool flag) { m_AIFlag = flag; }
	void SetPosition(DirectX::XMINT2 num);

	void StopedPlayer();

	bool GetAIFlag() { return m_AIFlag; }
	int GetMoney() { return m_Money; }

	void Reset();

	void AddMoney(int num);

private:
	bool m_AIFlag;
	DirectX::XMINT2 m_PosInt;
	bool m_MoveFlag;
	std::vector<DirectX::XMINT2> m_Route;
	int m_LastMove;
	PlayerNum m_PlayerNum;
	std::vector<int[2]> m_HaveStageNum;
	int m_Money;
	bool m_AnimeFlag;
	float m_MaxSize;
	float m_CurentSize;
};

