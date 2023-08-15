#pragma once
#include "ObjectBase.h"
class Player : public ObjectBase
{
public:
	Player();
	~Player();
	void Update() final;

	void SetAIFlag(bool flag) { m_AIFlag = flag; }

private:
	bool m_AIFlag;
};

