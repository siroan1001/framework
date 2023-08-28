#pragma once
#include "ObjectBase.h"
#include "Player.h"

class StageObject : public ObjectBase
{
public:
	StageObject(int x, int y, DirectX::XMFLOAT3* pPos);
	~StageObject() {};
	void Update() final {};

	void KeepStage(Player::PlayerNum playernum);
	void ReleaseStage();

private:
	static DirectX::XMFLOAT3* m_pParentPos;
	Player::PlayerNum m_HuvePlayer;
	int m_Lv;
};

