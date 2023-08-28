#pragma once
#include "ObjectBase.h"
#include "SceneGame.h"

class StageObject : public ObjectBase
{
public:
	StageObject(int x, int y, DirectX::XMFLOAT3* pPos);
	~StageObject() {};
	void Update() final {};

	void KeepStage(SceneGame::PlayerNum playernum);
	void ReleaseStage();

private:
	static DirectX::XMFLOAT3* m_pParentPos;
	SceneGame::PlayerNum m_HuvePlayer;
	int m_Lv;
};

