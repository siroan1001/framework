#pragma once
#include "GameUI.h"
#include <vector>

class CursorUI : public GameUI
{
public:
	CursorUI();
	void Update();

	void SetRot(float num) { m_Rot = num; }
	void SetMoveMax(float num) { m_maxMove = num; }
	void SetAnimeFrame(float num) { m_AnimeFrame = num; }

	DirectX::XMFLOAT3 GetForward();

private:
	float m_maxMove;
	float m_CurentMove;
	float m_AnimeFrame;
	bool m_MoveFlag;
	int m_CurentNum;
	std::vector<DirectX::XMFLOAT2> m_ChoicePos;
};

