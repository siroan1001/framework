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

public:
	const static int SIZE = 6;

private:
	StageObject* m_pStageOBj[SIZE][SIZE];

};

