#pragma once
#include "ObjectBase.h"
class Player : public ObjectBase
{
public:
	Player();
	~Player();
	void Update() final;

	void SetAIFlag(bool flag) { m_AIFlag = flag; }
	void SetPosition(DirectX::XMINT2 num);
private:
	bool m_AIFlag;
	DirectX::XMINT2 m_PosInt;
};

