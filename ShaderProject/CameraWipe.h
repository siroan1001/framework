#pragma once
#include "CameraBase.h"

class CameraWipe : public CameraBase
{
public:
	CameraWipe();
	~CameraWipe();
	void Update() final;
};