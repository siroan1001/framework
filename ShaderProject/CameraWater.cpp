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

	//�Q�Ƃ��Ă���J�����̐��ʂ���̍����Ɛ��ʉ��̃J�����̍������������Ȃ�悤�Ɍv�Z
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