#pragma once
#include "CameraBase.h"
#include <cmath>

class CameraGameMain : public CameraBase
{
public:
	CameraGameMain() { m_CamFlag = true; };
	~CameraGameMain() {};
	void Update() final {};

	DirectX::XMFLOAT3 GetRadius()
	{
		DirectX::XMFLOAT3 rad;
		DirectX::XMFLOAT3 base = DirectX::XMFLOAT3A(0.0f, 0.0f, 1.0f);

		DirectX::XMFLOAT3 delta = DirectX::XMFLOAT3(m_pos.x - base.x, m_pos.y - base.y, m_pos.z - base.z);
		float length = std::sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
		DirectX::XMFLOAT3 normalizedDeltaB = { delta.x / length, delta.y / length, delta.z / length };

		return rad;
	}
};

