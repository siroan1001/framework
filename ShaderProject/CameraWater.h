#pragma once
#include "CameraBase.h"
class CameraWater : public CameraBase
{
public:
	CameraWater();
	~CameraWater();
	void Update() final;

	void SetTargetCamera(CameraBase* pCam);
	void SetWaterPlaneHeight(float height);

private:
	CameraBase* m_pTarget;
	float m_waterHeight;
};

