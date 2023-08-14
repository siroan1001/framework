#pragma once
#include "ObjectBase.h"
class Dice : public ObjectBase
{
public:
	Dice();
	~Dice();
	void Update() final;

	int GetDiceNum() { return m_Num; }
	bool GetDiceFlag() { return m_RotFlag; }

private:
	void NumRot();

private:
	int m_Num;
	bool m_RotFlag;
};

