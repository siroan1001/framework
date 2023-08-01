#pragma once
#include "ObjectBase.h"

class StageObject : public ObjectBase
{
public:
	StageObject(int x, int y, DirectX::XMFLOAT3* pPos);
	~StageObject() {};
	void Update() final {};

private:
	static DirectX::XMFLOAT3* m_pParentPos;
};

