#pragma once
#include "ObjectBase.h"
class Dice : public ObjectBase
{
public:
	Dice();
	~Dice();
	void Update() final;
};

