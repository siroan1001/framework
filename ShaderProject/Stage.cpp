#include "Stage.h"

Stage::Stage()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			m_pStageOBj[j][i] = new StageObject(j, i, &m_Pos);
		}
	}
}

Stage::~Stage()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			delete m_pStageOBj[j][i];
		}
	}
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			m_pStageOBj[j][i]->Draw();
		}
	}
}
