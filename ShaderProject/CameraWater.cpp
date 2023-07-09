#include "CameraWater.h"

CameraWater::CameraWater()
	:m_pTarget(nullptr), m_waterHeight(0.0f)
{
}

CameraWater::~CameraWater()
{
}

void CameraWater::Update()
{
	if (!m_pTarget) { return; }

	m_pos = m_pTarget->GetPos();

	//参照しているカメラの水面からの高さと水面下のカメラの高さが等しくなるように計算
	m_pos.y = m_waterHeight - (m_pos.y - m_waterHeight);

	m_up = m_pTarget->GetUp();
	m_up.x *= -1;
	m_up.y *= -1;
	m_up.z *= -1;
}

void CameraWater::SetTargetCamera(CameraBase* pCam)
{
	m_pTarget = pCam;
}

void CameraWater::SetWaterPlaneHeight(float height)
{
	m_waterHeight = height;
}