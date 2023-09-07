#pragma once
#include "ObjectBase.h"
#include "StageObject.h"

class Stage : public ObjectBase
{
public:
	Stage();
	~Stage();
	void Update() final;
	void Draw();

	DirectX::XMFLOAT3 GetPosition(DirectX::XMINT2 num) { return m_pStageOBj[num.y][num.x]->GetPosition(); }
	StageObject* GetStageObj(DirectX::XMINT2 num) { return m_pStageOBj[num.y][num.x]; }

public:
	const static int SIZE = 4;

private:
	StageObject* m_pStageOBj[SIZE][SIZE];

};

