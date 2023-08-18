#pragma once
#include "ObjectBase.h"
class Dice : public ObjectBase
{
public:
	Dice();
	~Dice();
	void Update();

	int GetDiceNum() { return m_Num; }
	bool GetDiceFlag() { return m_RotFlag; }

	void Reset();

private:
	void NumRot();

private:
	int m_Num;
	bool m_RotFlag;
};

