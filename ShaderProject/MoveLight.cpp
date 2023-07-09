#include "MoveLight.h"
#include <algorithm>
#include "Input.h"

MoveLight::MoveLight()
	: m_radXZ(0.0f)
	, m_radY(DirectX::XM_PIDIV4)
	, m_hue(1.0f)
	, m_saturationValue(1.0f)
{
}
MoveLight::~MoveLight()
{
}

void MoveLight::Update()
{
	if (IsKeyPress('L'))
		UpdateParam();
}
void MoveLight::UpdateParam()
{
	// âÒì]
	constexpr float rotSpeed = DirectX::XMConvertToRadians(360.0f / (2.0f * 60)); // 2ïbÇ≈1âÒì]
	if (IsKeyPress('A')) { m_radXZ += rotSpeed; }
	if (IsKeyPress('D')) { m_radXZ -= rotSpeed; }
	if (IsKeyPress('W')) { m_radY += rotSpeed; }
	if (IsKeyPress('S')) { m_radY -= rotSpeed; }
	m_radY = std::min(std::max(m_radY, 0.0f), DirectX::XM_PIDIV2);

	const float lightLength = 5.0f;
	m_direction.x = cosf(m_radY) * sinf(m_radXZ) * lightLength;
	m_direction.y = -sinf(m_radY) * lightLength;
	m_direction.z = cosf(m_radY) * cosf(m_radXZ) * lightLength;

	m_pos.x = -m_direction.x;
	m_pos.y = -m_direction.y;
	m_pos.z = -m_direction.z;

	// êFïœçX
	if (IsKeyPress('R'))
	{
		m_saturationValue = 0.5f;
	}
	else
	{
		const float DefHueSpeed = 1.0f;
		const float SVSpeed = 0.01f;
		float HueSpeed = DefHueSpeed;
		if (IsKeyPress(VK_RCONTROL)) { HueSpeed *= 20.0f; }
		if (IsKeyPress(VK_RIGHT)) { m_hue += HueSpeed; }
		if (IsKeyPress(VK_LEFT)) { m_hue -= HueSpeed; }
		if (IsKeyPress(VK_UP)) { m_saturationValue += SVSpeed; }
		if (IsKeyPress(VK_DOWN)) { m_saturationValue -= SVSpeed; }
		if (m_hue < 0.0f) { m_hue += 360.0f; }
		if (m_hue > 360.0f) { m_hue -= 360.0f; }
		m_saturationValue = std::min(std::max(m_saturationValue, 0.0f), 1.0f);
	}
	m_diffuse = HSV2Color(m_hue, m_saturationValue);
}

void MoveLight::SetRot(float xz, float y)
{
	m_radXZ = xz;
	m_radY = y;
}
float MoveLight::GetRotXZ()
{
	return m_radXZ;
}
float MoveLight::GetRotY()
{
	return m_radY;
}

void MoveLight::SetHSV(float h, float sv)
{
	m_hue = std::min(std::max(h, 0.0f), 360.0f);
	m_saturationValue = std::min(std::max(sv, 0.0f), 1.0f);
	m_diffuse = HSV2Color(m_hue, m_saturationValue);
}
float MoveLight::GetH()
{
	return m_hue;
}
float MoveLight::GetSV()
{
	return m_saturationValue;
}

DirectX::XMFLOAT4 MoveLight::HSV2Color(float h, float sv)
{
	DirectX::XMFLOAT4 color(1.0f, 1.0f, 1.0f, 1.0f);

	h = h / 360.0f;
	sv = sv * 2.0f - 1.0f;
	float s = 1.0f - std::max(sv, 0.0f);
	float v = std::min(sv, 0.0f) + 1.0f;

	float r = v;
	float g = v;
	float b = v;
	if (s > 0.0f)
	{
		h *= 6.0f;
		int i = (int)h;
		float f = h - (float)i;
		switch (i)
		{
		default:
		case 0:
			g *= 1.0f - s * (1.0f - f);
			b *= 1.0f - s;
			break;
		case 1:
			r *= 1.0f - s * f;
			b *= 1.0f - s;
			break;
		case 2:
			r *= 1.0f - s;
			b *= 1.0f - s * (1.0f - f);
			break;
		case 3:
			r *= 1.0f - s;
			g *= 1.0f - s * f;
			break;
		case 4:
			r *= 1.0f - s * (1.0f - f);
			g *= 1.0f - s;
			break;
		case 5:
			g *= 1.0f - s;
			b *= 1.0f - s * f;
			break;
		}
	}

	color.x = r;
	color.y = g;
	color.z = b;
	return color;
}