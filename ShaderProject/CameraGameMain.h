#pragma once
#include "CameraBase.h"
class CameraGameMain : public CameraBase
{
public:
	CameraGameMain() { m_CamFlag = true; };
	~CameraGameMain() {};
	void Update() final {};
};

